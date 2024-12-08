/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 02:28:35 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/08 17:41:21 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_list(t_command_line *line)
{
	t_token	*current;

	current = line->first;
	while (current)
	{
		if (current->type < 0)
		{
			ft_error_token(current->content);
			return (EXIT_FAILURE);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_check_pipe(t_command_line *line)
{
	t_token	*current;
	t_token	*last;

	current = line->first;
	last = ft_lstlast_mini(line);
	if (current->type == PIPE || last->type == PIPE)
	{
		ft_error_pide("|");
		return (EXIT_FAILURE);
	}
	while (current->next)
	{
		if (current->type == PIPE && current->next->type == PIPE)
		{
			ft_error_pide("|");
			return (EXIT_FAILURE);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_check_redir(t_command_line *line)
{
	t_token	*current;
	t_token	*tmp;

	current = line->first;
	tmp = ft_lstlast_mini(line);
	if (!ft_isredirect(tmp->type))
		return (ft_error_end_redir(), EXIT_FAILURE);
	while (current->next)
	{
		if (!ft_isredirect(current->type)
			&& !ft_isredirect(current->next->type))
		{
			ft_error_double_redir(current->next->content);
			return (EXIT_FAILURE);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_check_pide_and_redir(t_command_line *line)
{
	t_token	*current;

	current = line->first;
	while (current->next)
	{
		if (!ft_isredirect(current->type) && current->next->type == PIPE)
		{
			ft_error_pide(current->content);
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
	if (ft_check_pide_and_redir(line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
