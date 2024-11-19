/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:17:16 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/16 17:00:50 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define DESTROY ((void *)-1)

typedef struct s_garbage 
{
	void				*ptr;
	struct s_garbage	*next;
	struct s_garbage	*prev;
}			t_garbage;

typedef struct s_gc
{
	t_garbage	*head;
	size_t		count_alloc;
	size_t		count_free;
}			t_gc;

//fonction utilitaire
void		*ft_malloc(long int size);
void		ft_free(void *ptr);

//fonction cachee
t_gc		*gc_init(void);
t_garbage	*create_node(t_gc *collector, void *ptr);
void		free_all(t_gc *garbage);
void		destroy(t_gc *garbage, void *elem);
int			in_garbage(t_gc *garbage, void *elem);


#endif