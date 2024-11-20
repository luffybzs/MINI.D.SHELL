/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:29:13 by utilisateur       #+#    #+#             */
/*   Updated: 2024/11/20 13:09:00 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_add_cmd(char *command, t_command_line *line, int *i)
{
	int	j;

	j = 0;
	while (command[*i + j] && !ft_isspace(command[*i + j])
		&& !ft_isseparator(command[*i + j]))
	{
		if (command[*i + j] == '\'' || command[*i + j] == '"')
			ft_next_char(command, command[*i + j], i, &j);
		if (command[*i + j])
			j++;
	}
	ft_add_token(ft_substr(command, *i, j), line);
	(*i) += j;
}

void	ft_add_redirect(char *command, t_command_line *line, int *i)
{
	char	*red;
	char	c;
	int		j;

	j = 0;
	c = command[*i];
	while (command[*i + j] == c)
		j++;
	red = malloc(sizeof(char) * (j + 1));
	if (!red)
		return ;
	j = 0;
	while (command[*i + j] == c)
	{
		red[j] = command[*i + j];
		j++;
	}
	red[j] = '\0';
	(*i) += j;
	ft_add_token(red, line);
}
