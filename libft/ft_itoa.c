/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:59:23 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/01 01:36:47 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	taille(int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	if (n == 0)
		i++;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	*str;
	long	nbr;

	nbr = n;
	i = taille(nbr);
	str = ft_malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	i--;
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		nbr = -nbr;
		str[0] = '-';
	}
	while (nbr != 0)
	{
		str[i--] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (str);
}

// int	main(void)
// {
// 	int numbers[] = {0, -9, -5, 00, 51, -2147483648};
// 	size_t num_count = sizeof(numbers) / sizeof(numbers[0]);

// 	for (size_t i = 0; i < num_count; i++)
// 	{
// 		char *str = ft_itoa(numbers[i]);
// 		if (str)
// 		{
// 			printf("Integer: %d -> String: %s\n", numbers[i], str);
// 			ft_free(str);
// 		}
// 		else
// 		{
// 			printf("Memory allocation failed for integer: %d\n", numbers[i]);
// 		}
// 	}

// 	return (0);
// }