/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:51:54 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/29 19:59:13 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

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
			sign *= -1;
		if (str[i + 1] == '\0')
			return (2147483648);
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - 48;
		i++;
		if (res * sign > 2147483647 || res * sign < -2147483648)
			return (2147483648);
	}
	return (res * sign);
}
static int is_it_num_or_egal(char *str)
{
	int i = 0;
	while(str[i])
	{
		if (str[i] != '-' && !(str[i] >= '0' && str[i] <= '9'))
			return (printf("exit: %s: numeric argument required\n", str),1);
		i++;
	}
	return (0);
}

static int is_valid_exit_arg(char *cmd)
{
	unsigned char value;
	// int i;

	if(is_it_num_or_egal(cmd) == 1)
		return (1);
	value = ft_atoi_spe(cmd);
	printf("valeur de l exit = %d\n", value);
	return (value);
}


int	ft_exit(t_shell *shell)
{
	t_exec	*current;
	int		i;

	i = 0;
	current = shell->first_exec;
	if (!current->cmd[1])
	{
		printf("passser le current cmd[1]\n");
		return (0);
		// retour de exit sans argument numerique
	}
	while (current->cmd[i])
		i++;
	if(i > 2)
		return (printf("exit: too many arguments\n"), shell->exit_status);
	i = 0;
	if (is_it_num_or_egal(current->cmd[1]) == 1)
		return(shell->exit_status);
	return (1);
}

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
// 	return 0;
	 
// }