/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:30:54 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/02 19:55:32 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_execute_command(t_shell *shell)
{
	t_token	*current;

	current = shell->command->first;
	if (is_builtin(current->content))
		return (execute_builtin(current, shell));
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

int	execute_builtin(t_token *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->content, "echo") == 0)
		return (ft_echo(cmd, shell));
	else if (ft_strcmp(cmd->content, "cd") == 0)
		return (ft_cd(shell));
	else if (ft_strcmp(cmd->content, "env") == 0)
		return (ft_env(shell));
	else if (ft_strcmp(cmd->content, "pwd") == 0)
		return (ft_pwd(shell));
	else if (ft_strcmp(cmd->content, "export") == 0)
		return (ft_export(shell));
	else if (ft_strcmp(cmd->content, "unset") == 0)
		return (ft_unset(shell));
	else if (ft_strcmp(cmd->content, "exit") == 0)
		return (ft_exit(shell));
	// implementer les autres builtins
	return (0);
}
