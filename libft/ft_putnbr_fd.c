/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:01:03 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/05/28 15:00:33 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	i;

	i = n;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-i, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(i / 10, fd);
		ft_putnbr_fd(i % 10, fd);
	}
	else if (n <= 9)
	{
		i = i + '0';
		write(fd, &i, 1);
	}
}
/*int	main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	ft_putnbr_fd(ft_atoi(av[1]), ft_atoi(av[2]));
	return (0);
}*/