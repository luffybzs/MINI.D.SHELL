/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:34:03 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/28 20:05:20 by ayarab           ###   ########.fr       */
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
		if (!prompt)
			return 0;
		if (ft_parsing_prompt(prompt, shell) == EXIT_FAILURE)
			continue ;
		// printf("%s\n", prompt);
	}
	return (EXIT_FAILURE);
}
void ft_fill_data(t_shell *shell, char **av)
{
	shell->shell_pid = getpid();
	shell->shell_name = ft_strdup(av[0]);
	shell->exit_status = 0;
}

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	t_shell	*shell;

	(void)ac;
	prompt = NULL;
	shell = env_init(env);
	if (!shell)
		return (printf("Failed to initialize shell environement\n"), 1);
	if (fill_env_list(shell) != 0)
		return (printf("Failed to initialize the linked environement list\n"),
				1); // needed to be freed later + retour d erreur
	ft_fill_data(shell,av);
	if (ft_loop_shell(prompt, shell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (0);
}
