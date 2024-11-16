/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 02:28:35 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/16 16:37:37 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_list(t_command_line *line)
{
	t_token	*current;
	int		i;

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

int	ft_check_pipe(t_command_line *line)
{
	t_token	*current;
	t_token	*last;

	current = line->first;
	last = ft_lstlast_mini(line);
	if (current->type == PIPE || last->type == PIPE)
	{
		ft_putstr_fd("|", 2);
		ft_putstr_fd(" ERROR PIPE\n", 2);
		return (EXIT_FAILURE);
	}
	while (current->next)
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
int	ft_check_redir(t_command_line *line)
{
	t_token	*current;

	current = line->first;
	while (current->next)
	{
		if (!ft_isredirect(current->type)
			&& !ft_isredirect(current->next->type))
		{
			ft_putstr_fd("MINI.D.SHELL: syntax error near unexpected token ",
							2);
			ft_putstr_fd("« ", 2);
			ft_putstr_fd(current->next->content, 2);
			ft_putstr_fd(" »\n", 2);
			return (EXIT_FAILURE);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_check_all_list(t_command_line *line)
{
	if (ft_check_list(line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_check_pipe(line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_check_redir(line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}