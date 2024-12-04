/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:48:42 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/04 18:41:24 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include <ncurses.h>
#include <term.h>

void	setup_interactive_signals(void)
{
	struct sigaction	sa;

	// Initialiser la structure sigaction à 0
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_interactive_signal;
	sa.sa_flags = SA_RESTART; // Redémarrer les appels système interrompus
	// Configurer SIGINT (Ctrl+C)
	sigaction(SIGINT, &sa, NULL);
	// Ignorer SIGQUIT (Ctrl+\)
	signal(SIGQUIT, SIG_IGN);
}

void	setup_execution_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_execution_signal;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void handle_interactive_signal(int signum)
{
    if (signum == SIGINT)
    {
        g_signal_status = signum;
        write(STDERR_FILENO, "\n", 1);
        rl_done = 1;
    }
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_interactive_signal;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN); 
}

void	handle_execution_signal(int signum)
{
	g_signal_status = 128 + signum;

	if (signum == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (signum == SIGINT)
		ft_putchar_fd('\n', STDERR_FILENO);
}