/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:34:25 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 16:02:58 by wdaoudi-         ###   ########.fr       */
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
	new_node->lock = false;
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

	if (!garbage)
		return ;
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
	free(garbage);
}

void	free_one(t_garbage *node)
{
	free(node->ptr);
	free(node);
}

void	free_unlock(t_gc *garbage)
{
	t_garbage	*prev;
	t_garbage	*current;
	t_garbage	*next;

	if (!garbage)
		return ;
	current = garbage->head;
	while (current)
	{
		prev = current->prev;
		next = current->next;
		if (current->lock == false)
		{
			if (prev)
				prev->next = next;
			if (next)
				next->prev = prev;
			if (current == garbage->head)
				garbage->head = next;
			free_one(current);
		}
		current = next;
	}
}
