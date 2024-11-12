/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:34:03 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/12 01:40:45 by ayarab           ###   ########.fr       */
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
		prompt = readline("./mini.d.shell ");
		if (ft_parsing_prompt(prompt, shell) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		printf("%s\n", prompt);
	}
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