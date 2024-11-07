/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:49:18 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/05/30 16:46:23 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(const char s, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*s2;
	size_t	i;
	size_t	j;
	size_t	k;

	k = 0;
	i = 0;
	j = ft_strlen(s1);
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (isset(s1[i], set) && s1)
		i++;
	while (isset(s1[j - 1], set) && j > i)
		j--;
	s2 = ft_calloc(j - i + 1, sizeof(char));
	if (!s2)
		return (NULL);
	while (i < j)
	{
		s2[k++] = s1[i++];
	}
	s2[k] = 0;
	return (s2);
}
// int	main(int ac, char **av)
// {
// 	if (ac == 0)
// 		return (0);
// 	printf("%s\n", ft_strtrim(av[1],av[2]));
// 	return (0);
// }