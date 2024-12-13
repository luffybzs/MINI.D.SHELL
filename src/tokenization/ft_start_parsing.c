/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:46:26 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/13 20:44:19 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../include/minishell.h"

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
			break ;
		if (prompt[i])
			ft_add_elem(line, prompt, &i);
	}
	return (line);
}

void	free_line(t_command_line *line)
{
	t_token	*current;
	t_token	*tmp;

	current = line->first;
	while (current)
	{
		tmp = current;
		current = current->next;
		ft_free(tmp->content);
		ft_free(tmp);
	}
	ft_free(line);
}
void	ft_display(t_command_line *line)
{
	t_token	*current;
	current = line->first;
	while (current)
	{
		printf("CONTENT -> [%s] | TOKEN -> [%d]\n ", current->content,
			current->type);
		// printf("[%s]", current->content);
		current = current->next;
		// if (current)
		// printf(" -> ");
		if (current)
			printf("           |\n"); //             \\/\n
	}
	printf("\nFIN DE LA PREMIER LIST\n");
}



int	ft_parsing_prompt_and_exec(char *prompt, t_shell *shell)
{
	t_command_line	*line;

	if (ft_check_open_quote(prompt) == EXIT_FAILURE)
		return (ft_error_quote(), EXIT_FAILURE);
	line = ft_loop_token(prompt);
	if (line->first == NULL)
		return (ft_free(line), EXIT_FAILURE);
	if (ft_check_all_list(line) == EXIT_FAILURE)
		return (free_line(line), EXIT_FAILURE);
	// ft_display(line);
	if (ft_expand(line, shell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	//ft_display(line);
	shell->command = line;
	if (ft_struc_for_exec(shell) == EXIT_FAILURE)
		return (free_line(line), EXIT_FAILURE);
	if (ft_check_heredoc(shell) == EXIT_FAILURE)
		return (free_line(line), EXIT_FAILURE);
	if (ft_start_exec(shell) == EXIT_FAILURE)
		return (free_line(line), EXIT_FAILURE);
	return (0);
}
