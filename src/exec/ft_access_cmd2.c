/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access_cmd2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab < ayarab@student.42.fr >            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:55:43 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/16 14:28:30 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	ft_exec_loop(t_shell *shell)
{
	t_exec			*current;
	struct termios	ter;
	int				status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	tcgetattr(STDOUT_FILENO, &ter);
	current = shell->first_exec;
	shell->previous_pipe_fd = -1;
	if (current->next == NULL && ft_execute_command(current, shell) != 0)
		return (tcsetattr(STDOUT_FILENO, TCSANOW, &ter), EXIT_SUCCESS);
	if (ft_fork(shell, current) == EXIT_FAILURE)
		return (tcsetattr(STDOUT_FILENO, TCSANOW, &ter), EXIT_FAILURE);
	tcsetattr(STDOUT_FILENO, TCSANOW, &ter);
	while (current)
	{
		if (waitpid(current->pidt, &status, 0) > 0)
			shell->exit_status = get_exit_status(status);
		current = current->next;
	}
	ft_check_signal_fork(shell);
	return (EXIT_SUCCESS);
}
