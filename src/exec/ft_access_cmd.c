/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:57:35 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/27 23:20:48 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_good_path(t_shell *shell, t_exec *current)
{
	int i;
	char *res;
	
	i = 0;
	if (access(current->cmd[0], F_OK | X_OK) == 0)
		return (ft_strdup(current->cmd[0]));	
	while (shell->path[i])
	{
		res = ft_strjoin(shell->path[i], "/");
		if (!res)
			return (NULL);
		res = ft_strjoin_free(res, current->cmd[0]);
		if (!res)
			return (NULL);
		if (access(res, F_OK | X_OK) == 0)
			return (res);
		free(res);
		i++;	
	}
	printf("%s not good\n", current->cmd[0]);
	return (NULL);
}


int ft_test(t_shell *shell)
{
	t_exec *current;
	char *goodpath;
	
	current = shell->exec_line->first;
	while (current)
	{
		goodpath = ft_good_path(shell, current);
		if (goodpath)
		{
			if (execve(goodpath, current->cmd, shell->env_upt) == -1)
				return (EXIT_FAILURE);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}