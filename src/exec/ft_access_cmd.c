/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:57:35 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/03 01:06:59 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_good_path(t_shell *shell, t_exec *current)
{
	int		i;
	char	*res;

	i = 0;
	if (!current->cmd || !shell->path)
		return (NULL);
	if (access(current->cmd[0], F_OK | X_OK) == 0)
		return (current->cmd[0]);
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
	perror(current->cmd[0]);
	return (NULL);
}
void	ft_open_infile(char *file, t_shell *shell)
{
	int	fd;

	(void)shell;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		ft_free(DESTROY);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}
void	ft_open_outfile(char *file, t_shell *shell)
{
	int	fd;

	(void)shell;
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(file);
		ft_free(DESTROY);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
void	ft_open_outfile_append(char *file, t_shell *shell)
{
	int	fd;

	(void)shell;
	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(file);
		ft_free(DESTROY);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_open_heredoc(t_redir *current, t_shell *shell)
{
	int	fd[2];

	(void)shell;
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Mini.D.Shell : Error pipe\n", 2);
		ft_free(DESTROY);
		exit(-1);
	}
	ft_putstr_fd(current->heredoc, fd[1]);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

int	ft_open_file(t_shell *shell, t_redir *current)
{
	while (current)
	{
		if (current->type == INFILE)
			ft_open_infile(current->file, shell);
		else if (current->type == OUTFILE)
			ft_open_outfile(current->file, shell);
		else if (current->type == APPEND)
			ft_open_outfile_append(current->file, shell);
		else if (current->type == END_OF_FILE)
			ft_open_heredoc(current, shell);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

void	ft_chill_exec(t_exec *current, t_shell *shell, int *fd)
{
	char	*goodpath;

	if (current->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (shell->previous_pipe_fd != -1)
		(dup2(shell->previous_pipe_fd, STDIN_FILENO), close(shell->previous_pipe_fd));
	if (current->redir)
		if (ft_open_file(shell, current->redir) == EXIT_FAILURE)
			(ft_free(DESTROY), exit(EXIT_FAILURE));
	if (!current->cmd || !current->cmd[0])
		(ft_free(DESTROY), exit(EXIT_SUCCESS));
	goodpath = ft_good_path(shell, current);
	if (!goodpath)
		(ft_free(DESTROY), exit(EXIT_FAILURE));
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
				return (perror("pipe"),EXIT_FAILURE);
		current->pidt = fork();
		if (current->pidt == -1)
			return (close(fd[0]), close(fd[1]), EXIT_FAILURE);
		if (current->pidt == 0)
			ft_chill_exec(current, shell, fd);
		if (current->next)
			close(fd[1]);
		if (shell->previous_pipe_fd != -1)
			close(shell->previous_pipe_fd);
		shell->previous_pipe_fd = fd[0];
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_exec_loop(t_shell *shell)
{
	t_exec *current;
	int status;
	current = shell->first_exec;

	shell->previous_pipe_fd = -1;
	if (ft_fork(shell, current) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (current)
	{
		waitpid(current->pidt, &status, 0);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}