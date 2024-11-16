/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:34:03 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/16 16:37:47 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

int	ft_loop_shell(char *prompt, t_shell *shell)
{
	while (1)
	{
		prompt = readline("Mini.D.Shell -> ");
		if (ft_parsing_prompt(prompt, shell) == EXIT_FAILURE)
			break ;
		// printf("%s\n", prompt);
	}
	return (EXIT_FAILURE);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *prompt = NULL;
	t_shell shell;
	shell.env = env;
	if (ft_loop_shell(prompt, &shell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (0);
}