/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:51:54 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/27 19:09:44 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_exit(t_shell *shell)
{
	t_exec	*current;
	int		i;

	i = 0;
	current = shell->exec_line->first;
	if (!current->cmd[1])
	{
		return (0);
		// retour de exit sans argument numerique
	}
	// while ()
}

/*
"exit: too many arguments" : si plus d'un argument
"exit: [arg]: numeric argument required" : si l'argument n'est pas numérique

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