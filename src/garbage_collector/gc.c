/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:33:33 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/15 18:26:46 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gc.h"

void	*ft_malloc(long int size)
{
	static t_gc	*garbage;
	void		*ptr;

	if (!garbage && size != -1)
		garbage = gc_init();
	if (size == -1)
	{
		garbage = NULL;
		return (NULL);
	}
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	create_node(garbage, ptr);
	if (!garbage->count_alloc)
		ft_free(garbage);
	garbage->count_alloc++;
	return (ptr);
}

void	ft_free(void *ptr)
{
	static int	i = -1;
	static t_gc	*garbage;

	if (ptr == DESTROY)
	{
		i = -1;
		free_all(garbage);
		garbage = ft_malloc(-1);
		return ;
	}
	if (!ptr)
		return ;
	if (i == -1)
	{
		garbage = ptr;
		i++;
		return ;
	}
	destroy(garbage, ptr);
	garbage->count_free++;
}
