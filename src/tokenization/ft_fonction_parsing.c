/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fonction_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:07:26 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/01 01:17:21 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exec_line	*ft_init_queue_exec(void)
{
	t_exec_line	*list;

	list = ft_malloc(sizeof(t_exec_line));
	if (!list)
		return (NULL);
	list->first = NULL;
	return (list);
}
int ft_nb_cmd(t_token *current)
{
	int nb;
	nb = 0;
	while (current)
	{
		if (current->type == WORD || current->type == SFX)
			nb++;
		if (current->type == PIPE)
			break;
		current = current->next;
	}
	return (nb);
}
int	ft_check_open_quote(char *prompt)
{
	int		i;
	char	quote;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' || prompt[i] == '"')
		{
			quote = prompt[i++];
			while (prompt[i] && prompt[i] != quote)
				i++;
			if (!prompt[i])
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
