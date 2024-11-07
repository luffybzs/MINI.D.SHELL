/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:18:49 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/05/28 20:01:50 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *aiguille, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(aiguille[j]))
		return ((char *)str);
	while (str[i] && i < len)
	{
		j = 0;
		while (i + j < len && str[i + j] && aiguille[j] && (str[i
					+ j] == aiguille[j]))
		{
			j++;
		}
		if (!aiguille[j])
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

/*int	main(int ac, char **av)
{
	if (ac < 2)
		return (0);
	printf("botte de foin : %s\n aiguille %s\n nombre de caractere cherche
		%d\n", av[1], av[2], atoi(av[3]));
	printf("resultat %s\n", ft_strnstr(av[1], av[2], atoi(av[3])));
	return (0);
}*/