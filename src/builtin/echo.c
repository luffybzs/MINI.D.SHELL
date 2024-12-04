/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:02:59 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/04 20:14:35 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_echo(t_exec *current, t_shell *shell)
{
	bool	newline;
	int		i;

	i = 1;
	newline = true;
	if (current->cmd[i] == "-n") // TODO: change whis later
	{
		i = ft_is_only_n(current->cmd);
		newline = false;
		if (!current->cmd[2])
			return (shell->exit_status = 1, 1);
		i++;
	}
	// open tout les fils et dup2 utilse t_redir ft_open
	while (tab[i])
	{
		ft_putstr_fd(current->cmd[i], 1); // remplacer par le futur fd
		if (current->cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline == true)
		ft_putchar_fd('\n', 1);
	return (shell->exit_status = 0, 0);
}

int	ft_is_only_n(char **tab)
{
	int	i;
	int	j;

	i = 1;
	while (tab[i])
	{
		if (tab[i][0] != '-' || tab[i][1] == '\0')
			return (i);
		j = 1;
		while (tab[i][j])
		{
			if (tab[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

