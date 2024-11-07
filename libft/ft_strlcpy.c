/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:54:29 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/05/28 21:09:01 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lenght;

	i = 0;
	lenght = 0;
	while (src[lenght])
		lenght++;
	if (!(size > 0))
		return (lenght);
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (lenght);
}

/*int main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	printf("dst avant: %s\n", av[1]); // dst
	printf("src avant: %s\n", av[2]);
	printf("taille maximale de copie: %lu\n", strlen(av[2])); // lenght de av[2]

	size_t result = strlcpy(av[1], av[2], strlen((av[2])));
	printf("dst: %s\n", av[1]); // dst
	printf("src: %s\n", av[2]);
	printf("longueur de src: %zu\n", result); // zu => imprimer un size_t
	return (0);
}*/