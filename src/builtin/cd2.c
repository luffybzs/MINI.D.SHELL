/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:50:44 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 16:53:12 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	handle_cd_args(t_exec *current, t_shell *shell)
{
	if (current->cmd[1] && current->cmd[2])
	{
		ft_putstr_fd(shell->shell_name, 2);
		ft_putstr_fd(": cd: too many arguments\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

int	execute_cd(char *path, char *old_pwd, t_shell *shell)
{
	if (chdir(path) != 0)
	{
		handle_cd_error(path, shell);
		return (1);
	}
	if (update_pwd_env(shell, old_pwd))
	{
		shell->exit_status = 1;
		return (1);
	}
	shell->exit_status = 0;
	return (0);
}

int	ft_cd(t_exec *current, t_shell *shell)
{
	char	*path;
	char	*old_pwd;
	int		ret;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (shell->exit_status = 1, 1);
	if (handle_cd_args(current, shell))
		return (ft_free(old_pwd), 1);
	if (!current->cmd[1])
	{
		if (handle_cd_no_args(shell, &path))
			return (ft_free(old_pwd), 1);
	}
	else
		path = current->cmd[1];
	ret = execute_cd(path, old_pwd, shell);
	ft_free(old_pwd);
	return (ret);
}
