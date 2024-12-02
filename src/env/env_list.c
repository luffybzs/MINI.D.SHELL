/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:49:34 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/02 17:27:49 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gc.h"
#include "../../include/minishell.h"

int	fill_env_list(t_shell *shell)
{
	int		i;
	t_env	*new;
	t_env	*current;

	i = 0;
	while (shell->env[i])
	{
		new = create_env_node(shell->env[i]);
		if (!new)
			return (-1);
		if (!shell->head)
			shell->head = new;
		else
		{
			current = shell->head;
			while (current->next)
				current = current->next;
			current->next = new;
		}
		i++;
	}
	return (0);
}

t_env	*create_env_node(char *env_str)
{
	t_env	*new;
	int		sep_index;

	new = ft_malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	sep_index = ft_findchar(env_str, '=');
	if (sep_index == -1)
		return (free(new), NULL);
	new->key = ft_substr(env_str, 0, sep_index);
	new->value = ft_substr(env_str, sep_index + 1, ft_strlen(env_str)
			- sep_index);
	if (!new->key || !new->value)
	{
		free_env_node(new);
		return (NULL);
	}
	ft_lock(new);
	ft_lock(new->key);
	ft_lock(new->value);
	new->next = NULL;
	return (new);
}

void	free_env_list(t_shell *shell)
{
	t_env	*current;
	t_env	*next;

	if (!shell || !shell->head)
		return ;
	current = shell->head;
	while (current)
	{
		next = current->next;
		free_env_node(current);
		current = next;
	}
	shell->head = NULL;
}

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

int	ft_findchar(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}
