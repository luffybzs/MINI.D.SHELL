/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:49:34 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 16:25:36 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gc.h"
#include "../../include/minishell.h"

char	*get_shell_level(char **env)
{
	int		i;
	char	*shlvl_value;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			shlvl_value = get_incremented_shlvl(env[i] + 6);
			return (shlvl_value);
		}
		i++;
	}
	return (ft_strdup("1"));
}

t_env	*create_shlvl_node(char *shlvl_value)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup("SHLVL");
	new->value = ft_strdup(shlvl_value);
	new->next = NULL;
	ft_lock(new);
	ft_lock(new->key);
	ft_lock(new->value);
	return (new);
}

void	add_to_env_list(t_env *new, t_shell *shell)
{
	t_env	*current;

	if (!shell->head)
		shell->head = new;
	else
	{
		current = shell->head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

int	fill_env_list(t_shell *shell)
{
	int		i;
	t_env	*new;
	char	*shlvl_value;

	i = 0;
	if (!shell->env || !shell->env[0])
		return (0);
	shlvl_value = get_shell_level(shell->env);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "SHLVL=", 6) == 0)
			new = create_shlvl_node(shlvl_value);
		else
			new = create_env_node(shell->env[i]);
		if (!new)
			return (ft_free(shlvl_value), -1);
		add_to_env_list(new, shell);
		i++;
	}
	return (ft_free(shlvl_value), 0);
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
		return (ft_free(new), NULL);
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
