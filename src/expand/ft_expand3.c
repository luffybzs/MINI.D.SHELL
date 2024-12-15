/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:18:09 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/15 17:59:14 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	handle_part_expand(char *expanded, t_token *current, t_token *prev,
// 		t_command_line *line)
// {
// 	int		i;
// 	char	**split_word;
// 	t_token	*new_token;
// 	t_token	*next_save;

// 	// (void)current;
// 	// (void)line;
// 	i = 0;
// 	if (!expanded || !current || !line)
// 		return (EXIT_FAILURE);
// 	next_save = current->next;
// 	split_word = ft_split(expanded, ' ');
// 	if (!split_word)
// 		return (EXIT_FAILURE);
// 	while (split_word[i] != NULL)
// 		i++;
// 	if (i <= 1)
// 		return (ft_free_2d(split_word), 1);
// 	i = 0;
// 	while (split_word[i])
// 	{
// 		new_token = ft_malloc(sizeof(t_token));
// 		if (!new_token)
// 			return (ft_free_2d(split_word), EXIT_FAILURE);
// 		new_token->content = ft_strdup(split_word[i]);
// 		new_token->type = current->type;
// 		if (prev)
// 			prev->next = new_token;
// 		else
// 			line->first = new_token;
// 		prev = new_token;
// 		i++;
// 	}
// 	if (prev)
// 		prev->next = next_save;
// 	ft_free_2d(split_word);
// 	// ft_free(current->content);
// 	// ft_free(current);
// 	// ft_display(line);
// 	return (0);
// }

static t_token	*init_new_token(char *content, int type)
{
	t_token	*new_token;

	new_token = ft_malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(content);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

static void	update_token_list(t_token *new, t_token **prev,
		t_command_line *line)
{
	if (*prev)
		(*prev)->next = new;
	else
		line->first = new;
	*prev = new;
}

static int	add_tokens(char **split_word, t_token *current,
		t_token **prev, t_command_line *line)
{
	t_token	*new_token;
	int		i;

	i = 0;
	while (split_word[i])
	{
		new_token = init_new_token(split_word[i], current->type);
		if (!new_token)
			return (EXIT_FAILURE);
		update_token_list(new_token, prev, line);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	handle_part_expand(char *expanded, t_token *current,
		t_token *prev, t_command_line *line)
{
	char	**split_word;
	t_token	*next_save;

	if (!expanded || !current || !line)
		return (EXIT_FAILURE);
	split_word = ft_split(expanded, ' ');
	if (!split_word)
		return (EXIT_FAILURE);
	if (ft_strlen_2d(split_word) <= 1)
		return (ft_free_2d(split_word), EXIT_SUCCESS);
	next_save = current->next;
	if (add_tokens(split_word, current, &prev, line) == EXIT_FAILURE)
		return (ft_free_2d(split_word), EXIT_FAILURE);
	if (prev)
		prev->next = next_save;
	return (ft_free_2d(split_word), EXIT_SUCCESS);
}
