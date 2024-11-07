/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:11:20 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/06/05 13:28:00 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list		*lstt;

	while (*lst)
	{
		lstt = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = lstt;
	}
	free(*lst);
	*lst = NULL;
}
