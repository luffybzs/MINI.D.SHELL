/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:48:09 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/10 17:01:32 by wdaoudi-         ###   ########.fr       */
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
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
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
void	ft_end_exit(t_shell *shell, int status, t_exec *current)
{
	(void)shell;
	if (current->pidt != 0)
	{
		ft_free(DESTROY);
		exit(status);
	}
	else
	{
		ft_free(PROMPT);
		exit(status);
	}
}

static int	check_numeric_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && (arg[i] == ' ' || arg[i] == 't'))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_exec *current, t_shell *shell)
{
	int		is_parent;
	long	value;
	int		exit_val;

	is_parent = (current->pidt != 0);
	if (!current->cmd[1])
	{
		exit_val = shell->exit_status;
		if (is_parent)
			ft_putstr_fd("exit\n", 1);
		if (!current->next)
		{
			if (current->pidt == 0)
				exit(exit_val);
			ft_free(DESTROY);
			exit(exit_val);
		}
		// g_signal_status = exit_val;
		shell->exit_status = exit_val;
		return (0);
	}
	if (current->cmd[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		// g_signal_status = 1;
		shell->exit_status = 1;
		return (1);
	}
	value = ft_atoi_spe(current->cmd[1]);
	if (!check_numeric_arg(current->cmd[1]) || value == 2147483648)
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit_val = 2;
		if (is_parent)
			ft_putstr_fd("exit\n", 1);
		if (!current->next)
		{
			if (current->pidt == 0)
				exit(exit_val);
			ft_free(DESTROY);
			exit(exit_val);
		}
		// g_signal_status = exit_val;
		shell->exit_status = exit_val;
		return (0);
	}
	exit_val = (unsigned char)value;
	if (is_parent)
		ft_putstr_fd("exit\n", 1);
	if (!current->next)
	{
		if (current->pidt == 0)
			exit(exit_val);
		ft_free(DESTROY);
		exit(exit_val);
	}
	// g_signal_status = exit_val;
	shell->exit_status = exit_val;
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