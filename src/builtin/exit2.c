/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:45:10 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 16:49:23 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include <limits.h>

int	handle_no_args(t_exec *current, t_shell *shell)
{
	int	exit_val;

	exit_val = shell->exit_status;
	if (current->pidt != 0)
		ft_putstr_fd("exit\n", 1);
	if (!current->next)
		ft_end_exit(shell, exit_val, current);
	shell->exit_status = exit_val;
	return (0);
}

int	handle_numeric_error(t_exec *current, t_shell *shell)
{
	if (current->pidt != 0)
		ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("exit: numeric argument required\n", 2);
	if (!current->next)
		ft_end_exit(shell, 2, current);
	shell->exit_status = 2;
	return (0);
}

int	ft_exit(t_exec *current, t_shell *shell)
{
	long	value;
	int		exit_val;

	if (!current->cmd[1])
		return (handle_no_args(current, shell));
	if (current->cmd[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	value = ft_atoi_spe(current->cmd[1]);
	if (!check_numeric_arg(current->cmd[1]) || value == 2147483648)
		return (handle_numeric_error(current, shell));
	exit_val = (unsigned char)value;
	if (current->pidt != 0)
		ft_putstr_fd("exit\n", 1);
	if (!current->next)
		ft_end_exit(shell, exit_val, current);
	shell->exit_status = exit_val;
	return (0);
}
