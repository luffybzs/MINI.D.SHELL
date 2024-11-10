/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:13:35 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/06/04 19:02:04 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*new_node;

// 	head = ft_lstnew("World");
// 	new_node = ft_lstnew("Hello");
// 	ft_lstadd_front(&head, new_node);
// 	if (head == new_node && head->next != NULL && head->next->content != NULL)
// 		printf("First Node: %s\nSecond Node: %s\n", (char *)head->content,
// 			(char *)head->next->content);
// 	else
// 		printf("ft_lstadd_front failed\n");
// 	return (0);
// }
// first : hello
// second  world