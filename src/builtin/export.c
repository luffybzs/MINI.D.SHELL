/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:02:29 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/26 15:34:07 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_export(t_shell *shell)
{
	char	*looking_for;
	t_exec	*current;
	int i;
	
	i = 1;
	printf("entrer dans la boucle export\n");
	current = shell->exec_line->first;
	if (!current->cmd[0] || !current->cmd[1])
		return (printf("encore moins a gratter"), 1);
	// censer afficheer les variable exporte
	while (shell->exec_line->first->cmd[i])
	{
	looking_for = shell->exec_line->first->cmd[i];
	if (!looking_for)
		return (printf("rien a gratter\n"), 1); // gerer l erreur
	if (is_name_ok(looking_for, shell) == 1)
		return (printf("%d\n", is_name_ok(looking_for, shell)), 0);
	i++;
	}
	printf("parfait\n");
	return (0);
}

int	is_name_ok(char *str, t_shell *shell)
{
	int	i;

	i = 0;
	if ((str[i] != '_' && !ft_isalpha(str[i])) || str[i] == '=')
		return (printf("%s: export '%s': not a valid identifier\n",
				shell->shell_name, str), 1); // gerer l erreur
	i++;
	while (str[i] && str[i] != '=')
	{
		if ((str[i] != '_' && !ft_isalpha(str[i]) && !ft_isalnum(str[i])
				&& str[i] != '='))
			return (printf("%s: export '%s': not a valid identifier\n",
					shell->shell_name, str), 1); // gerer l erreur
		i++;
	}
	return (0);
}
// rependre dedans et continuer les verification avant de modifier sur la liste chaionee

/*
if first caractere is not a _ or a letter error:
bash-5.1$ export  5test=abc
bash: export: `5test=abc': not a valid identifier

sensible a la casse :
bash-5.1$ export test = abc
bash: export: `=': not a valid identifier

bash: export: `=': not a valid identifier
bash-5.1$ export test =abc
bash: export: `=abc': not a valid identifier
bash-5.1$ export test= abc
bash-5.1$ env | grep test
test=

en cas d espace avant le egale errror et apres
le bash prends "test=''"


test des quotes:
test='abc' && test="abc" => test=abc
expand similaire aux autres expand

error:

export 1test    # "not a valid identifier"
export	A = 1    # "not a valid identifier"
export readonly # Si variable en lecture seule: "readonly variable"

*/