/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:11:39 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/06/04 19:52:59 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
// void print_content(void *content) {
//     printf("%s\n", (char *)content);
// }

// int main() {
//     t_list *head = ft_lstnew("First");
//     t_list *second = ft_lstnew("Second");
//     ft_lstadd_back(&head, second);

//     ft_lstiter(head, print_content);
//     return 0;
// }

//first 
// second