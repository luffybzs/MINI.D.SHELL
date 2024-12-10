/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:03:08 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/10 17:20:59 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (current->heredoc)
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
