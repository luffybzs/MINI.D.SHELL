/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:34:03 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/05 03:27:04 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t	g_signal_status = 100;

int	ft_loop_shell(char *prompt, t_shell *shell)
{
	while (1)
	{
		ft_signal();
		prompt = readline("Mini.D.Shell -> ");
		if (g_signal_status != 100)
		{
			g_signal_status = 100;
			continue ;
		}
		if (!prompt)
			break ;
		if (*prompt)
			add_history(prompt);
		if (ft_parsing_prompt(prompt, shell) == EXIT_FAILURE)
			shell->exit_status = 2;
	}
	return (EXIT_FAILURE);
}
void	ft_fill_data(t_shell *shell, char **av)
{
	shell->shell_pid = getpid();
	shell->shell_name = ft_strdup(av[0]);
	shell->exit_status = 0;
	shell->previous_pipe_fd = -1;
}

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	t_shell	shell;

	(void)ac;
	/* signaux*/
	// setup_interactive_signals();
	prompt = NULL;
	memset(&shell, 0, sizeof(t_shell));
	shell.env = env;
	if (fill_env_list(&shell) != 0)
		return (printf("Failed to initialize the linked environement list\n"),
				1); // needed to be freed later + retour d erreur
	ft_fill_data(&shell, av);
	if (ft_loop_shell(prompt, &shell) == EXIT_FAILURE)
		return (ft_free(DESTROY), EXIT_FAILURE);
	return (ft_free(DESTROY), 0);
}

// int main(void)
// {
// 	struct sigaction sa;
// 	(void)sa;
// 	printf("size of sigaction : %lu\n", sizeof(struct sigaction));
// 	return (0);
// }
