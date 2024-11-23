/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:31:33 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/23 19:38:35 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exec_line	*ft_init_queue_exec(void)
{
	t_exec_line	*list;

	list = malloc(sizeof(t_exec_line));
	if (!list)
		return (NULL);
	list->first = NULL;
	return (list);
}


int ft_start_cmd(t_shell *shell)
{
	t_exec_line *line;

	line = ft_init_queue_exec();
	
}

