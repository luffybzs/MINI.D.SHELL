/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:53:27 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/08 06:43:44 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_S_PRINTF_H
# define FT_S_PRINTF_H


# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define EGAL ==
# define IS =
# define IS_NOT !=

 
typedef struct s_data
{
	char tmp[10000];
	int i;
	int j;
} t_data;


int		ft_s_printf(char *dst,const char *str, ...);
int		ft_putstr(const char *str, t_data *data, int j);
int		ft_putchar(const char c,t_data *data, int j);
int		ft_strlen_printf(const char *str);
long	ft_putnbr_base(unsigned long n, char *base, t_data *data, int j);
int		sign_check(long n, char *base, t_data *data,int j);

#endif