/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_the_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 00:42:24 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/06 15:30:40 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



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

char	**ft_search_path(t_shell *shell)
{
	char	**tab;

	tab = ft_way_path(shell);
	if (!tab)
		return (NULL);
	return (tab);
}

int	ft_get_env(t_shell *shell)
{
	char	**tab;
	char	**path;

	tab = ft_lst_strdup(shell);
	if (!tab)
		return (EXIT_FAILURE);
	shell->env_upt = tab;
	path = ft_search_path(shell);
	if (!path)
		return (EXIT_FAILURE);
	shell->path = path;
	return (EXIT_SUCCESS);
}

int	ft_start_exec(t_shell *shell)
{
	if (ft_get_env(shell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_exec_loop(shell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}