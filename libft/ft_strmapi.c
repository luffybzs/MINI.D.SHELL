/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:40:52 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/01 01:36:47 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = ft_malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	while (i < ft_strlen(s))
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}

/*char    ttolower(unsigned int down, char a)
{
	(void) down;
	if (a >= 'A' && a <= 'Z')
	{
		a += 32;
	}
	return (a);
}

char	ttoupper(unsigned int a, char    c)
{
	(void) a;
	if (c >= 'a' && c <= 'z')
	{
		c -= 32;
	}
	return (c);
}
int	main(void)
{
	char *test1 = "abcdef5ABCDEF1515";
	char *test2 = "ABCDEF15abcdef115";
	char *result;

	printf("avant t1: %s\n", test1);
	printf("avant t2: %s\n", test2);
	result = ft_strmapi(test2, ttolower);
	if (result)
	{
		printf("t1 %s\n", result);
		ft_free(result);
	}

	result = ft_strmapi(test1, ttoupper);
	if (result)
	{
		printf("t2: %s\n", result);
		ft_free(result);
	}
	return (0);
}*/