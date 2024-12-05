/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:48:21 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/05 03:55:43 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_env(t_exec *actual, t_shell *shell)
{
	t_env	*current;

	// t_exec *cmd;
	if (!actual || !actual->cmd || !shell || !shell->head)
	{
		ft_putstr_fd("env: cannot run command\n", 2);
		shell->exit_status = 127;
		return (EXIT_FAILURE);
	}
	if (actual->cmd[1] && actual->cmd[1][0] == '-')
	{
		ft_putstr_fd("env: illegal option\n", 2);
		shell->exit_status = 125;
		return (EXIT_FAILURE);
	}
	if (actual->cmd[1]) // Si des arguments sont passés
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		shell->exit_status = 125;
		return (EXIT_FAILURE);
	}
	current = shell->head;
	while (current)
	{
		if (current->value[0] != 0)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	shell->exit_status = 0;
	return (EXIT_SUCCESS);
}
