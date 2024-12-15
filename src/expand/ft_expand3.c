/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:18:09 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/15 13:30:45 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_part_expand(char *expanded, t_token *current, t_token *prev,
		t_command_line *line)
{
	int		i;
	char	**split_word;
	t_token	*new_token;
	t_token	*next_save;

	// (void)current;
	// (void)line;
	i = 0;
	if (!expanded || !current || !line)
		return (EXIT_FAILURE);
	next_save = current->next;
	split_word = ft_split(expanded, ' ');
	if (!split_word)
		return (EXIT_FAILURE);
	while (split_word[i] != NULL)
		i++;
	if (i <= 1)
		return (ft_free_2d(split_word), 1);
	i = 0;
	while (split_word[i])
	{
		new_token = ft_malloc(sizeof(t_token));
		if (!new_token)
			return (ft_free_2d(split_word), EXIT_FAILURE);
		new_token->content = ft_strdup(split_word[i]);
		new_token->type = current->type;
		if (prev)
			prev->next = new_token;
		else
			line->first = new_token;
		prev = new_token;
		i++;
	}
	if (prev)
		prev->next = next_save;
	ft_free_2d(split_word);
	// ft_free(current->content);
	// ft_free(current);
	// ft_display(line);
	return (0);
}
