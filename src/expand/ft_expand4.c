/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:01:17 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/16 13:58:39 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_token_expansion(t_token *current, t_token **prev,
		t_command_line *line, t_shell *shell)
{
	char	*expanded;

	expanded = expand_var(current->content, shell, current);
	if (!expanded)
		return (EXIT_SUCCESS);
	if (current->type == WORD && ft_strchr(expanded, ' '))
	{
		if (handle_part_expand(expanded, current, *prev, line) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (2);
	}
	ft_free(current->content);
	current->content = expanded;
	return (EXIT_SUCCESS);
}

static t_token	*get_next_token(t_token *prev, t_command_line *line)
{
	if (prev)
		return (prev->next);
	return (line->first);
}

static void	ft_define_expand(t_token **current, t_token **prev,
		t_command_line *line)
{
	*current = line->first;
	*prev = NULL;
}

int	ft_expand(t_command_line *line, t_shell *shell)
{
	t_token	*current;
	t_token	*prev;
	int		expand_status;

	ft_define_expand(&current, &prev, line);
	while (current)
	{
		if (current->type == END_OF_FILE)
		{
			prev = current;
			current = current->next;
			continue ;
		}
		expand_status = handle_token_expansion(current, &prev, line, shell);
		if (expand_status == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (expand_status == 2)
		{
			current = get_next_token(prev, line);
			continue ;
		}
		prev = current;
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	handle_special_var(char c, int *i, t_expand_state *state, t_shell *shell)
{
	char	*tmp;

	if (c == '?')
	{
		tmp = ft_itoa(shell->exit_status);
		append_string(&state->result, tmp);
		ft_free(tmp);
		(*i)++;
		return (1);
	}
	else if (c == '0')
	{
		append_string(&state->result, shell->shell_name);
		(*i)++;
		return (1);
	}
	return (0);
}
