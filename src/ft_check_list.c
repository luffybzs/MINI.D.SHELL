/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 02:28:35 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/16 04:46:18 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_check_list(t_command_line *line)
{
	t_token *current;
	int i;
	i = 0;
	current = line->first;
	while (current)
	{
		if (current->type < 0)
			{
				ft_putstr_fd(current->content, 2);
				ft_putstr_fd(" ERROR INVALID TOKEN\n", 2);
				i = EXIT_FAILURE;
			}
		current = current->next;
	}
	return (i);
}

int ft_check_pipe(t_command_line *line)
{
	t_token *current;
	t_token *last;
	

	current = line->first;
	last = ft_lstlast_mini(line);
	if (current->type == PIPE || last->type == PIPE)
		{
			ft_putstr_fd("|", 2);
			ft_putstr_fd(" ERROR PIPE\n", 2);
			return (EXIT_FAILURE);
		}
	while (current)
	{
		if (current->type == PIPE && current->next->type == PIPE)
		{
			ft_putstr_fd(current->content, 2);
			ft_putstr_fd(" ERROR PIPE\n", 2);
			return (EXIT_FAILURE);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int ft_check_all_list(t_command_line *line)
{
	if (ft_check_list(line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_check_pipe(line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
		
	return (EXIT_SUCCESS);
}