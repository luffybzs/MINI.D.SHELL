/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:29:47 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/05/27 14:54:17 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = 0;
		ptr++;
		n--;
	}
}

/*int main() {
	char buffer[10];

	// Initialisation du buffer avec des valeurs non nulles
	memset(buffer, 'A', sizeof(buffer));

	// Afficher le contenu du buffer avant d'appeler bzero
	printf("Buffer avant bzero: ");
	for (int i = 0; i < sizeof(buffer); i++) {
		printf("%c ", buffer[i]);
	}
	printf("\n");

	// Appel de la fonction bzero pour mettre à zéro les 5 premiers octets
	bzero(buffer, 5);

	// Afficher le contenu du buffer après avoir appelé bzero
	printf("Buffer après bzero: ");
	for (int i = 0; i < sizeof(buffer); i++) {
		if (buffer[i] == 0) {
			printf("0 ");
		} else {
			printf("%c ", buffer[i]);
		}
	}
	printf("\n");

	return (0);
}*/