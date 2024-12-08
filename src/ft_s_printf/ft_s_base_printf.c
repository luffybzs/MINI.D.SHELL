/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_base_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:37:38 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/08 05:42:57 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_s_printf.h"

long	ft_putnbr_base(unsigned long n, char *base, t_data *data, int j)
{
	unsigned long	baselen;
	unsigned long	i;
	(void) j;
	
	baselen = ft_strlen_printf(base);
	i = 0;
	if (n >= baselen)
	{
		i += ft_putnbr_base(n / baselen, base, data, j);
		i += ft_putnbr_base(n % baselen, base, data, j);
	}
	else
	{
		data->tmp[data->j] = base[n];
		i++;
		data->j++;
	}
	return (i);
}

int	sign_check(long n, char *base ,t_data *data ,int j)
{
	(void) j;
	if (n < 0)
	{
		data->tmp[data->j] = '-';
		data->j++;
		return (ft_putnbr_base(-n, base, data , j));
	}
	return (ft_putnbr_base(n, base, data, j));
}
