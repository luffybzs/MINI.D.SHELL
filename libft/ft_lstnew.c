/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:54:47 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/01 01:17:21 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = ft_malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// int main() {
//     t_list *node = ft_lstnew("Hello");
//     if (node != NULL && node->content != NULL)
//         printf("Content: %s\n", (char *)node->content);
//     else
//         printf("ft_lstnew failed\n");
//     return 0;
// }

//attendue :content: hello