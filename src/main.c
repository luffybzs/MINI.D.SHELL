/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:34:03 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/13 23:11:58 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t	g_signal_status = 0;

static int	handle_prompt_input(char *prompt, t_shell *shell)
{
	if (g_signal_status != 0)
	{
		shell->exit_status = g_signal_status;
		g_signal_status = 0;
		return (1);
	}
	if (!prompt)
	{
		ft_putstr_fd("exit\n", 1);
		return (-1);
	}
	if (*prompt)
		add_history(prompt);
	return (ft_parsing_prompt_and_exec(prompt, shell));
}

int	ft_loop_shell(char *prompt, t_shell *shell)
{
	int	i;
	int	ret;

	i = 0;
	while (1)
	{
		shell->nb_line++;
		g_signal_status = 0;
		if (i > 255)
			i = 0;
		ft_signal();
		prompt = readline(ft_print_color(i));
		ret = handle_prompt_input(prompt, shell);
		i += 3;
		if (ret == -1)
			break ;
		if (ret == 1)
			continue ;
	}
	return (EXIT_SUCCESS);
}
// if (g_signal_status != 0)
// {
// 	shell->exit_status = g_signal_status;
// 	g_signal_status = 0;
// 	continue ;
// }
// if (!prompt)
// {
// 	printf("exit\n");
// 	break ;
// }
// if (*prompt)
// 	add_history(prompt);
// ft_parsing_prompt_and_exec(prompt, shell);

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	t_shell	shell;
	(void)ac;
	prompt = NULL;
	ft_memset(&shell, 0, sizeof(t_shell));
	shell.env = env;
//	tcgetattr(STDIN_FILENO, )
	ft_fill_data(&shell, av);
	if (!isatty(0))
		return (printf("tty required!!\n"), 1);
	if (fill_env_list(&shell) != 0)
		return (printf("Failed to initialize the environement\n"), 1);
	if (ft_loop_shell(prompt, &shell) == EXIT_SUCCESS)
		return (ft_free(DESTROY), EXIT_SUCCESS);
	return (ft_free(DESTROY), 0);
}
