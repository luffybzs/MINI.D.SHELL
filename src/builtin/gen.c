/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:12:38 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/04 21:21:06 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_execute_command(t_exec *current, t_shell *shell)
{
	if (is_builtin(current->cmd[0]))
	{
		execute_builtin(current, shell);
		return (1);
	}
	return (0); // envoyer vers gestion hors builtin
}
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_exec *current, t_shell *shell)
{
	if (ft_strcmp(current->cmd[0], "echo") == 0)
		ft_echo(current, shell);
	else if (ft_strcmp(current->cmd[0], "cd") == 0)
		ft_cd(shell);
	else if (ft_strcmp(current->cmd[0], "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(current->cmd[0], "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp(current->cmd[0], "export") == 0)
		ft_export(shell);
	else if (ft_strcmp(current->cmd[0], "unset") == 0)
		ft_unset(shell);
	else if (ft_strcmp(current->cmd[0], "exit") == 0)
		ft_exit(shell);
	// implementer les autres builtins
	return ;
}
