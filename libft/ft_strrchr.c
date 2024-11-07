/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:11:46 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/05/27 14:50:04 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	cc;

	cc = (char)c;
	i = 0;
	while (s[i])
		i++;
	while (i > 0)
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i--;
	}
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (NULL);
}

/*int main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	printf ("string : %s\n char : %s\n resultat: %s\n", av[1], av[2],
		ft_strrchr(av[1], av[2][0]));
	return (0);
}*/