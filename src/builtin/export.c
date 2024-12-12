/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:02:29 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 16:32:08 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	handle_export_arg(char *arg, t_shell *shell)
{
	t_env	*existing;

	if (is_name_ok(arg, shell))
		return (1);
	existing = ft_find_env(shell, arg);
	if (!existing)
		add_new_env(arg, shell);
	else if (ft_strchr(arg, '='))
	{
		ft_free(existing->value);
		existing->value = get_value(arg);
	}
	return (0);
}

int	ft_export(t_exec *current, t_shell *shell)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!current->cmd[1])
	{
		ft_export_without_arg(shell);
		shell->exit_status = 0;
		return (0);
	}
	while (current->cmd[i])
	{
		if (handle_export_arg(current->cmd[i], shell))
			status = 1;
		i++;
	}
	shell->exit_status = status;
	return (status);
}

void	print_identifier_error(char *str, t_shell *shell)
{
	ft_putstr_fd(shell->shell_name, 2);
	ft_putstr_fd(": export: `", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	check_empty_name(char *str, t_shell *shell)
{
	if (!str || str[0] == '\0')
	{
		print_identifier_error(str, shell);
		return (1);
	}
	return (0);
}

int	check_first_char(char *str, t_shell *shell)
{
	if (str[0] != '_' && !ft_isalpha(str[0]))
	{
		print_identifier_error(str, shell);
		return (1);
	}
	return (0);
}

/*commande env: affiche toute la liste chainee
 qui possede une value
diffference avec export sans argument qui
 affihce toute la liste chainee sans distinction

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