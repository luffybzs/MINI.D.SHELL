/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:17:20 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/05/28 21:10:51 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

/*int main(int ac, char **av)
{
	if (ac != 4)
		return (0);
	printf(":premiere chaine %s\n deuxieme chaine
		%s\n nombre de caractere compare max %d\n",av[1], av[2], atoi(av[3]));
	printf("resultat: %d\n", ft_strncmp(av[1], av[2], atoi(av[3])));
	return (0);
}*/