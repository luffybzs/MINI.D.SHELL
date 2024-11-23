/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:48:26 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/23 15:56:27 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int ft_pwd(t_shell *shell)
{
	t_env *current;

	current = shell->head;
	while (current)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0) // ne marche pas il faut utlise la fonction getcwd psk si je unset le chemin il faut comme le trouvrer
		{
			printf("%s\n", current->value);
			return (EXIT_SUCCESS);
		}
		current = current->next;
	}
	return (EXIT_FAILURE);
}