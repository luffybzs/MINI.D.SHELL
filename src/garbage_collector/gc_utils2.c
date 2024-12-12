/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:02:23 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 16:02:52 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gc.h"

void	destroy(t_gc *garbage, void *elem)
{
	t_garbage	*current;

	if (!garbage)
		return ;
	if (!in_garbage(garbage, elem))
	{
		free(elem);
		return ;
	}
	current = garbage->head;
	while (current->ptr != elem)
		current = current->next;
	if (current->prev)
		current->prev->next = current->next;
	else
		garbage->head = current->next;
	if (current->next)
		current->next->prev = current->prev;
	free(current->ptr);
	free(current);
}

int	in_garbage(t_gc *garbage, void *elem)
{
	t_garbage	*current;

	current = garbage->head;
	while (current)
	{
		if (current->ptr == elem)
			return (1);
		current = current->next;
	}
	return (0);
}
