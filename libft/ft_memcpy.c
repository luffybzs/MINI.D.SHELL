/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:30:58 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/05/30 18:39:14 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr2;
	unsigned char	*ptr1;
	size_t			i;

	if (!src && !dest)
		return (NULL);
	ptr2 = (unsigned char *)dest;
	ptr1 = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		ptr2[i] = ptr1[i];
		i++;
	}
	return (dest);
}

/*int main(int ac, char **av)
{
	if(ac != 4)
		return (0);
 printf("Source : %s\n", av[2]);

	memcpy(av[1], av[2], atoi(av[3]));

	av[1][atoi(av[3])] = '\0';

	printf("Destination : %s\n", av[1]);

	return (0);
}*/