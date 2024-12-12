/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 03:10:44 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 16:50:26 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static int	is_valid_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_print_echo(char *s, int fd)
{
	size_t	check;

	check = write(fd, s, ft_strlen(s));
	if (check != ft_strlen(s))
		return (ft_putstr_fd("echo: write error: No space left on device\n", 2),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_echo(t_exec *current, t_shell *shell)
{
	int		i;
	bool	newline;

	(void)shell;
	i = 1;
	newline = true;
	while (current->cmd[i] && is_valid_n_option(current->cmd[i]))
	{
		newline = false;
		i++;
	}
	while (current->cmd[i])
	{
		if (ft_print_echo(current->cmd[i], 1) == EXIT_FAILURE)
			return (shell->exit_status = 1, 1);
		if (current->cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	g_signal_status = 0;
	shell->exit_status = 0;
	return (0);
}
