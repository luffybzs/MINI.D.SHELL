/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_the_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 00:42:24 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/27 23:25:41 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_len_env(t_shell *shell)
{
	t_env *current;
	int i;
	
	i = 0;
	current = shell->head;
	while (current->next)
	{
		i++;
		current = current->next;
	}
	return (i);
}
char *ft_cpy_env(char *key, char *value)
{
	char *res;
	
	res = ft_strdup(key);
	if (!res)
		return (NULL);
	res = ft_strjoin(res, "=");
	if (!res)
		return (NULL);
	res = ft_strjoin(res, value);
	if (!res)
		return (NULL);
	return (res);
}

char **ft_lst_strdup(t_shell *shell)
{
	t_env *current;
	char **env_cpy;
	int len;
	int i;
	
	i = 0;
	len = ft_len_env(shell);
	env_cpy = malloc(sizeof(char *) * (len + 1));
	if (!env_cpy)
		return (NULL);
	current = shell->head;
	while (current)
	{
		env_cpy[i] = ft_cpy_env(current->key, current->value);
		if (!env_cpy[i])
			return (NULL);
		i++;
		current = current->next;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}
char	**ft_way_path(t_shell *shell)
{
	int		j;
	char	*res;
	char	**tab;

	j = 0;
	if (!shell->env_upt)
		return (NULL);
	while (shell->env_upt[j])
	{
		if (ft_strnstr(shell->env_upt[j], "PATH=", 5) != NULL)
		{
			res = ft_strdup(shell->env_upt[j] + 5);
			if (!res)
				return (NULL);
			tab = ft_split(res, ':');
			if (!tab)
				return (NULL);
			return (tab);
		}
		j++;
	}
	return (NULL);
}

char **ft_search_path(t_shell *shell)
{
	char **tab;
	
	tab = ft_way_path(shell);
	if (!tab)
		return (NULL);
	return (tab); 
}

int ft_get_env(t_shell *shell)
{
	char **tab;
	char **path;
	 
	tab = ft_lst_strdup(shell);
	if (!tab)
		return (EXIT_FAILURE);
	shell->env_upt = tab;
	path = ft_search_path(shell); 
	if (!path)
		return (EXIT_FAILURE);
	shell->path = path;
	if (ft_test(shell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}