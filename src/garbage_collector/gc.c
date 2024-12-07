/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:33:33 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/07 20:39:00 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gc.h"

#define GET 1
#define SET 0

t_gc	*_garbage(t_gc *garbage, int flag)
{
	static t_gc	*save = NULL;

	if (flag == SET)
		save = garbage;
	return (save);
}

void	*ft_malloc(long int size)
{
	t_gc	*garbage;
	void	*ptr;

	garbage = _garbage(NULL, GET);
	if (!garbage && size != -1)
		garbage = _garbage(gc_init(), SET);
	if (size == -1)
	{
		garbage = _garbage(NULL, SET);
		return (NULL);
	}
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	create_node(garbage, ptr);
	garbage->count_alloc++;
	return (ptr);
}

void	ft_free(void *ptr)
{
	t_gc	*garbage;

	garbage = _garbage(NULL, GET);
	if (ptr == DESTROY)
	{
		free_all(garbage);
		_garbage(NULL, SET);
		return ;
	}
	if (ptr == PROMPT)
	{
		free_unlock(garbage);
		return ;
	}
	if (!ptr)
		return ;
	destroy(garbage, ptr);
	garbage->count_free++;
}

void	ft_lock(void *ptr)
{
	t_gc		*garbage;
	t_garbage	*current;

	garbage = _garbage(NULL, GET);
	current = garbage->head;
	while (current)
	{
		if (current->ptr == ptr)
		{
			current->lock = true;
			return ;
		}
		current = current->next;
	}
}

void	ft_unlock(void *ptr)
{
	t_gc		*garbage;
	t_garbage	*current;

	garbage = _garbage(NULL, GET);
	current = garbage->head;
	while (current)
	{
		if (current->ptr == ptr)
		{
			current->lock = false;
			return ;
		}
		current = current->next;
	}
}
