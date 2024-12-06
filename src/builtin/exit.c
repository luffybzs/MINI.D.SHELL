/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:48:09 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/06 14:37:58 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include <limits.h>

static long	ft_atoi_spe(char *str)
{
	size_t		i;
	long int	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (2147483648);
		if (res > LONG_MAX / 10 ||
			(res == LONG_MAX / 10 && (str[i] - '0') > LONG_MAX % 10))
			return (2147483648);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

static int	check_numeric_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	handle_exit_error(int error_type)
{
	if (error_type == 1)
		ft_putstr_fd("exit: too many arguments\n", 2);
	else if (error_type == 2)
		ft_putstr_fd("exit: numeric argument required\n", 2);
}

static void	exit_with_value(long value)
{
	ft_putstr_fd("exit\n", 1);
	exit((unsigned char)value);
}

int	ft_exit(t_exec *current, t_shell *shell)
{
	long	value;

	if (!current->cmd[1])
	{
		ft_putstr_fd("exit\n", 1);
		exit(shell->exit_status);
	}
	if (current->cmd[2])
	{
		handle_exit_error(1);
		shell->exit_status = 1;
		return (1);
	}
	if (!check_numeric_arg(current->cmd[1]))
	{
		handle_exit_error(2);
		exit(2);
	}
	value = ft_atoi_spe(current->cmd[1]);
	if (value == 2147483648)
	{
		handle_exit_error(2);
		exit(2);
	}
	exit_with_value(value);
	return (0);
}


/* 
attention double free a l input de deux arguments a gerer avec 
le garbage */
/*
"exit: [arg]: numeric argument required" :
si l'argument n'est pas numérique

1.Validation numérique stricte : seulement [-]?[0-9]+
	isalnum et cmd[1] peut etre egale a '-',
	sinon return(1) et print error;

2.Plage acceptée : 0 à 255 après modulo
	atoi, %256;

3.Gestion des long long pour éviter les overflows
	atoi spe, long long;


4.Conversion du string en nombre avec gestion d'erreurs
	itoa...;
*/

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	unsigned char	test;
// 	test = ft_atoi_spe(av[1]);
// 	printf("valeur de test = %d", test);
// 	return (0);

// }