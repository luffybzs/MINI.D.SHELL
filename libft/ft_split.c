/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:58:36 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/01 01:36:47 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	size_t	i;
	int		n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			n++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (n);
}

int	lenght_word(char const *s, char c, int i)
{
	int	n;

	n = 0;
	while (s[i + n] != c && s[i + n])
		n++;
	return (n);
}

void	*ft_free_split(char **str, int count)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (i < count)
	{
		ft_free(str[i]);
		i++;
	}
	ft_free(str);
	return (NULL);
}

char	**sous_split(char const *s, char c, char **str)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		k = 0;
		str[j] = ft_malloc((lenght_word(s, c, i) + 1) * sizeof(char));
		if (str[j] == NULL)
			return (ft_free_split(str, j));
		while (s[i] && s[i] != c)
			str[j][k++] = s[i++];
		str[j][k] = 0;
		while (s[i] == c && s[i])
			i++;
		j++;
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = ft_malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (str == NULL)
		return (str);
	return (sous_split(s, c, str));
}
