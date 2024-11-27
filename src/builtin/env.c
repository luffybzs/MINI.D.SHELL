/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:48:21 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/27 18:23:41 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_env(t_shell *shell)
{
	t_env *current;

	current = shell->head;
	while (current)
	{
		if (current->value[0] != 0)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}