/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_printf_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:18:28 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/08 05:36:21 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_s_printf.h"

int	ft_putchar(const char c, t_data *data, int j)
{
	data->tmp[j] = c;
	return (1);
}
char *ft_strcat(char *dest, const char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

int	ft_putstr(const char *str, t_data *data, int j)
{
	int	i;

	i = 0;
	if (!str)
	{
		return (ft_putstr("(null)", data, j));
	}
	while (str[i])
	{
		data->tmp[j] = str[i];
		i++;
		j++;
	}
	return (i);
}

int	ft_strlen_printf(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
