/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:46:26 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/19 22:36:19 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h" 

void	ft_add_elem(t_command_line *line, char *command, int *i)
{
	if (is_redirect(&command[*i]))
		ft_add_redirect(command, line, i);
	else if (!is_redirect(&command[*i]))
		ft_add_cmd(command, line, i);
}

t_command_line	*ft_loop_token(char *prompt)
{
	int				i;
	t_command_line	*line;

	line = ft_init_queue();
	if (!line)
		return (NULL);
	i = 0;
	while (prompt[i])
	{
		if (ft_skip_spaces(prompt, &i) == EXIT_FAILURE)
			return (line);
		if (prompt[i])
		{
			ft_add_elem(line, prompt, &i);
		}
	}
	return (line);
}

void	ft_display(t_command_line *line)
{
	t_token	*current;

	current = line->first;
	while (current)
	{
		printf("CONTENT -> [%s] | TOKEN -> [%d]\n ", current->content,
				current->type);
		//printf("[%s]", current->content);
		current = current->next;
		//if (current)
		//printf(" -> ");
		if (current)
			printf("           |\n"); //             \\/\n
	}
	printf("\n");
}

int	ft_parsing_prompt(char *prompt, t_shell *shell)
{
	t_command_line *line;

	(void)shell;
	if (ft_check_open_quote(prompt) == EXIT_FAILURE)
		return (ft_error_quote(), EXIT_FAILURE);
	line = ft_loop_token(prompt);
	if (line == NULL)
		return (EXIT_FAILURE);
	if (ft_check_all_list(line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
 
	shell->command = line;
	//if(ft_execute_command(shell) == EXIT_FAILURE)
	//	return(EXIT_FAILURE);
	ft_display(line);
	return (0);
}