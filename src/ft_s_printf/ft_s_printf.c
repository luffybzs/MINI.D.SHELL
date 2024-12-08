/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:00:39 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/08 06:40:46 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_s_printf.h"

void	ft_check_character(va_list *av, char c, t_data *data, int j)
{
	if (c == 'c')
		data->j += ft_putchar(va_arg(*av, int), data, j);
	else if (c == 's')
		data->j += ft_putstr(va_arg(*av, char *), data,j);
	else if (c == 'd' || c == 'i')
		sign_check((long)va_arg(*av, int), "0123456789", data, j);
	else if (c == 'x')
		sign_check((long)va_arg(*av, unsigned int), "0123456789abcdef", data, j);
	else if (c == 'X')
		sign_check((long)va_arg(*av, unsigned int), "0123456789ABCDEF", data , j);
	else if (c == 'u')
		sign_check((long)va_arg(*av, unsigned int), "0123456789", data, j);
	else
	{
		data->j += ft_putchar('%',data,j);
		data->j += ft_putchar(c, data, j);	
	}
}

void fill_data(t_data *data)
{
	data->i = 0;
	data->j = 0;
}

#include <stdio.h>

int	ft_s_printf(char *dst,const char *str, ...)
{
	va_list	list;
	t_data data;
	va_start(list, str);

	if (!str)
		return (-1);
	fill_data(&data);
	while (str[data.i])
	{
		if (str[data.i] == '%')
		{
			ft_check_character(&list, str[data.i + 1], &data, data.j);
			data.i += 2;
		}
		else 
		{
			data.tmp[data.j] = str[data.i];
			data.j++;
			data.i++;
		}	
	}
	(void)dst;
	data.tmp[data.j] = '\0';
	memcpy(dst, data.tmp, 10000);
	return (va_end(list),data.j);
}
