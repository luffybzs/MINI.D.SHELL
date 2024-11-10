/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:34:03 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/10 21:23:48 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include<readline/readline.h>
#include <stdio.h>
#include "minishell.h"

int ft_check_open_quote(char *prompt)
{
	int i;
	char c;
	
	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' || prompt[i] == '"')
		{
			c = prompt[i++];
			while (prompt[i] && prompt[i] != c)
				i++;
			if (!prompt)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}


int ft_parsing_prompt(char *prompt, t_shell *shell)
{
	if (ft_check_open_quote(prompt) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_tokenization(prompt,shell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
		
}






int  ft_loop_shell(char *prompt, t_shell *shell)
{
	while(1)
	{
		prompt = readline("./mini.d.shell ");
		ft_parsing_prompt()
		printf("%s\n");
	}
}


int main(int ac, char **av, char **env)
{
	(void)	ac;
	(void)  av;
	char *prompt;
	t_shell shell;
	shell.env = env;
	if (ft_loop_shell(prompt, &shell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	return (0);
}