/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:30:36 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 17:40:25 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

// void	add_to_env_list(t_shell *shell, t_env *new)
// {
// 	t_env	*current;

// 	if (!shell->head)
// 		shell->head = new;
// 	else
// 	{
// 		current = shell->head;
// 		while (current->next)
// 			current = current->next;
// 		current->next = new;
// 	}
// }

void	add_new_env(char *str, t_shell *shell)
{
	t_env	*new;
	char	*equal_sign;

	if (!str || !shell)
		return ;
	new = init_env_node();
	if (!new)
		return ;
	equal_sign = ft_strchr(str, '=');
	if (!set_key_value(new, str, equal_sign))
	{
		ft_free_env_node(new);
		return ;
	}
	add_to_env_list(new, shell);
}

int	ft_export_without_arg(t_shell *shell)
{
	t_env	*current;

	current = shell->head;
	while (current)
	{
		if (current->value[0])
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("declare -x %s\n", current->key);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

void	*ft_free_env_node(t_env *node)
{
	if (!node)
		return (NULL);
	if (node->key)
		ft_free(node->key);
	if (node->value)
		ft_free(node->value);
	ft_free(node);
	return (NULL);
}
