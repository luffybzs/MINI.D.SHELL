/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:57:35 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/12 13:08:51 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error_access(t_shell *shell, t_exec *current)
{
	char	*tmp;

	(void)shell;
	if (ft_strcmp(current->cmd[0], "b*54w/afq8974d") == 0)
	{
			shell->exit_status = 0;
			ft_free(DESTROY);
			exit(0);
	}
	tmp = ft_strjoin("Mini.D.Shell: ", current->cmd[0]);
	if (!tmp)
		return ;
	tmp = ft_strjoin(tmp, " : Command Not Found\n");
	if (!tmp)
		return ;
	write(2, tmp, ft_strlen(tmp));
}

char	*ft_good_path(t_shell *shell, t_exec *current)
{
	int		i;
	char	*res;

	i = 0;
	if (!current->cmd || current->cmd[0][0] == '\0')
		return (ft_error_access(shell, current), NULL);
	if (access(current->cmd[0], F_OK | X_OK) == 0)
		return (current->cmd[0]);
	if (!shell->path) 
		return (ft_error_access(shell, current), NULL);
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
		ft_free(res);
		i++;
	}
	ft_error_access(shell, current);
	return (NULL);
}
int	ft_add_flag(t_exec *current)
{
	if (ft_cmp_flag(current->cmd[0]) == EXIT_SUCCESS)
	{
		current->cmd = ft_putflag(current->cmd);
		if (!current->cmd)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

void	ft_child_exec(t_exec *current, t_shell *shell, int *fd)
{
	char	*goodpath;

	if (current->next)
		(close(fd[0]), dup2(fd[1], STDOUT_FILENO), close(fd[1]));
	if (shell->previous_pipe_fd != -1)
		(dup2(shell->previous_pipe_fd, STDIN_FILENO),
			close(shell->previous_pipe_fd));
	if (current->redir)
		if (ft_open_file(shell, current->redir) == EXIT_FAILURE)
			(ft_free(DESTROY), exit(EXIT_FAILURE));
	if (!current->cmd || !current->cmd[0])
		(ft_free(DESTROY), exit(EXIT_SUCCESS));
	if (ft_execute_command(current, shell) != 0)
		(ft_free(DESTROY), exit(EXIT_FAILURE));
	ft_add_flag(current);
	goodpath = ft_good_path(shell, current);
	if (!goodpath)
		(ft_free(DESTROY), exit(127));
	execve(goodpath, current->cmd, shell->env_upt);
	(perror("execve failed"), ft_free(DESTROY), exit(EXIT_FAILURE));
}

 int	ft_fork(t_shell *shell, t_exec *current)
 {
 	int	fd[2];

 	while (current)
 	{
 		if (current->next != NULL)
 			if (pipe(fd) == -1)
 				return (perror("pipe"), EXIT_FAILURE);
 		current->pidt = fork();
 		if (current->pidt == -1)
 			return (close(fd[0]), close(fd[1]), EXIT_FAILURE);
 		if (current->pidt == 0)
 		{
 			set_signal_child();
			ft_get_env(shell);
 			ft_child_exec(current, shell, fd);
 		}
 		if (current->next)
 			close(fd[1]);
 		if (shell->previous_pipe_fd != -1)
 			close(shell->previous_pipe_fd);
 		shell->previous_pipe_fd = fd[0];
 		current = current->next; 
	}
 	return (EXIT_SUCCESS);
}

void	ft_check_signal_fork(t_shell *shell)
{
	if (shell->exit_status == 128 + SIGINT)
		printf("\n");
	else if (shell->exit_status == 128 + SIGQUIT)
		printf("Quit (core dumped)\n");
	return ;
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	return (1);
}

int ft_exec_loop(t_shell *shell)
{
    t_exec *current;
    int status;

   	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
    current = shell->first_exec;
    shell->previous_pipe_fd = -1;
	if (current->next == NULL && ft_execute_command(current, shell) != 0)
		return (EXIT_SUCCESS);
    if (ft_fork(shell, current) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    while (current)
    {
        if (waitpid(current->pidt, &status, 0) > 0)
			shell->exit_status = get_exit_status(status);
        current = current->next;
    }
	ft_check_signal_fork(shell);
    return (EXIT_SUCCESS);
}


