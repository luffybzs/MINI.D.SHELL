/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:29:38 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/16 13:53:45 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	nbr;
	int	i;
	int	signe;

	i = 0;
	signe = 1;
	nbr = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == 45)
	{
		signe = -signe;
		i++;
	}
	else if (nptr[i] == 43)
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		nbr = (nbr * 10) + nptr[i] - '0';
		i++;
	}
	return (nbr * signe);
}
/*int	main(int ac, char *av[])
{
	if (ac != 2)
		return (0);
	else
	{
		printf("%d\n", ft_atoi(av[1]));
		printf("%d\n", atoi(av[1]));
	}
	return (0);
}*/