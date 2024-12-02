/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:02:25 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/02 17:29:43 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_unset(t_shell *shell)
{
	t_exec	*current;
	int		status;
	int		i;

	i = 1;
	status = 0;
	current = shell->first_exec;
	if (!shell || !shell->first_exec || !current->cmd)
		return (1);
	if (!current->cmd)
		return (1);
	if (!current->cmd[1])
		return (0);
	while (current->cmd[i])
	{
		if (is_name_ok_unset(current->cmd[i], shell))
			status = 1;
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

void	looking_and_sup(char *str, t_shell *shell)
{
	t_env	*current;
	t_env	*previous;
	char	*equal_sign;
	size_t	key_len;

	if (!shell || !shell->head || !str)
		return ;
	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
		key_len = (size_t)(equal_sign - str);
	else
		key_len = ft_strlen(str);
	current = shell->head;
	previous = NULL;
	while (current)
	{
		if (ft_strlen(current->key) == key_len && !ft_strncmp(str, current->key,
				key_len))
		{
			if (!previous)
				shell->head = current->next;
			else
				previous->next = current->next;
			ft_free_env_node(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}
