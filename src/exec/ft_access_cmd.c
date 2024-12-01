/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:57:35 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/01 14:07:30 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_good_path(t_shell *shell, t_exec *current)
{
	int i;
	char *res;
	
	i = 0;
	if (!current->cmd || !shell->path)
		return (NULL);
	printf("current->cmd[0] == [%s]\n", current->cmd[0]);
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
	//printf("%s not good\n", current->cmd[0]);
	return (NULL);
}
void ft_open_infile(char *file,t_shell *shell)
{
	int fd;
	(void) shell;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		// fermer le promt et passe a la prochaine cmd -- faudrait une fonction quitte et ft_free tout sauf l'env
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}
void ft_open_outfile(char *file, t_shell *shell)
{
	int fd;
	(void) shell;
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(file);
		// same pour la ferme le promt
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
void ft_open_outfile_append(char *file, t_shell *shell)
{
	int fd;
	(void) shell;
	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(file);
		// err 
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void ft_open_heredoc(t_redir *current, t_shell *shell)
{
	int fd[2];
	(void) shell;
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Mini.D.Shell : Error pipe\n", 2);
		exit(-1);
	}
	ft_putstr_fd(current->heredoc, fd[1]);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

int ft_open_file(t_shell *shell,t_redir *current)
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
			ft_open_heredoc(current,shell);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int ft_fork(t_shell *shell,t_exec *current)
{
	int fd[2];

	char *goodpath;
	while (current)
	{
		if (current->next != NULL)
		{
			if(pipe(fd) == -1)
				return (EXIT_FAILURE);
		}
		current->pidt = fork();
		if (current->pidt == -1)
		{
			close(fd[0]);
			close(fd[1]);
			return (EXIT_FAILURE);
		}
		if (current->pidt == 0)
		{
			if (current->next)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			if (current->redir)
			{
				if (ft_open_file(shell,current->redir) == EXIT_FAILURE)
					exit(EXIT_FAILURE);
			}
			
			if (!current->cmd || !current->cmd[0])
				exit(EXIT_SUCCESS);
			goodpath = ft_good_path(shell, current);
			if (!goodpath)
				exit(EXIT_FAILURE);
			execve(goodpath,current->cmd,shell->env_upt);
		}
		if (current->next)
			close(fd[1]);
		if (current->next)
			close(fd[0]);
		current = current->next;
	}
	return(EXIT_SUCCESS);
}


int ft_exec_loop(t_shell *shell)
{
	t_exec *current;
	int status;
	current = shell->first_exec;
	
	if (ft_fork(shell, current) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	while (current)
	{
		waitpid(current->pidt,&status, 0);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}