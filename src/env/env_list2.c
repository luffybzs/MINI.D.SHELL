/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:23:48 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 16:25:34 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gc.h"
#include "../../include/minishell.h"

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
		ft_free(node->key);
	if (node->value)
		ft_free(node->value);
	ft_free(node);
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

char	*get_incremented_shlvl(char *current_shlvl)
{
	int		level;
	char	*new_shlvl;

	if (!current_shlvl || !*current_shlvl)
		level = 1;
	else
	{
		level = ft_atoi(current_shlvl);
		if (level < 0)
			level = 0;
		else
			level++;
	}
	new_shlvl = ft_itoa(level);
	return (new_shlvl);
}
