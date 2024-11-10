/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:20:25 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/06/05 12:09:10 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

// int main() {
//     t_list *head = ft_lstnew("One");
//     ft_lstadd_front(&head, ft_lstnew("Two"));
//     ft_lstadd_front(&head, ft_lstnew("Three"));
//     printf("List size: %d\n", ft_lstsize(head));
//     return (0);
// }
// lst size: 3