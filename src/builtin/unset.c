/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:02:25 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/10 17:03:06 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_unset(t_exec *current, t_shell *shell)
{
	int	status;
	int	i;

	// t_exec	*current;
	i = 1;
	status = 0;
	// g_signal_status = 0;
	shell->exit_status = 0;
	if (!shell || !shell->first_exec || !current->cmd)
		return (shell->exit_status = 1, 1);
	if (!current->cmd[1])
		return (shell->exit_status = 0, 0);
	while (current->cmd[i])
	{
		if (is_name_ok_unset(current->cmd[i], shell))
		{
			// g_signal_status = 1;
			shell->exit_status = 1;
			status = 1;
		}
		else
		{
			looking_and_sup(current->cmd[i], shell);
		}
		i++;
	}
	return (status);
}

int	is_name_ok_unset(char *str, t_shell *shell)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (printf("%s: unset '%s': not a valid identifier\n",
				shell->shell_name, str), 1);
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (printf("%s: unset '%s': not a valid identifier\n",
				shell->shell_name, str), 1);
	while (str[i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (printf("%s: unset '%s': not a valid identifier\n",
					shell->shell_name, str), 1);
		i++;
	}
	return (0);
}

static size_t	get_key_length(char *str)
{
	char	*equal_sign;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
		return ((size_t)(equal_sign - str));
	return (ft_strlen(str));
}

static void	remove_node(t_env *current, t_env *prev, t_shell *shell)
{
	if (!prev)
		shell->head = current->next;
	else
		prev->next = current->next;
	ft_free_env_node(current);
}

void	looking_and_sup(char *str, t_shell *shell)
{
	t_env	*current;
	t_env	*prev;
	size_t	key_len;

	if (!shell || !shell->head || !str)
		return ;
	key_len = get_key_length(str);
	current = shell->head;
	prev = NULL;
	while (current)
	{
		if (ft_strlen(current->key) == key_len && !ft_strncmp(str, current->key,
				key_len))
		{
			remove_node(current, prev, shell);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
