/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:34:25 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/01 01:27:32 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gc.h"

t_gc	*gc_init(void)
{
	t_gc	*collector;

	collector = malloc(sizeof(t_gc));
	if (!collector)
		return (NULL);
	collector->head = NULL;
	collector->count_alloc = 0;
	collector->count_free = 0;
	return (collector);
}

t_garbage	*create_node(t_gc *collector, void *ptr)
{
	t_garbage	*new_node;
	t_garbage	*current;

	new_node = malloc(sizeof(t_garbage));
	if (!new_node)
		return (NULL);
	new_node->ptr = ptr;
	new_node->prev = NULL;
	if (!collector->head)
		collector->head = new_node;
	else
	{
		current = collector->head;
		while (current->next)
			current = current->next;
		current->next = new_node;
		new_node->prev = current;
	}
	new_node->next = NULL;
	return (new_node);
}

void	free_all(t_gc *garbage)
{
	t_garbage	*current;
	t_garbage	*next;

	if (garbage)
	{
		if (!garbage->head)
		{
			free(garbage);
			return ;
		}
		current = garbage->head;
		while (current)
		{
			next = current->next;
			free(current->ptr);
			free(current);
			current = next;
		}
	}
	free(garbage);
}

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
