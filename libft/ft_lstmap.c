/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:12:02 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/06/05 15:35:54 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*listt;
	t_list	*maillon;

	if (!lst || !f || !del)
		return (NULL);
	listt = NULL;
	while (lst)
	{
		maillon = ft_lstnew(f(lst->content));
		if (!maillon)
		{
			ft_lstclear(&listt, del);
			return (NULL);
		}
		ft_lstadd_back(&listt, maillon);
		lst = lst->next;
	}
	return (listt);
}
