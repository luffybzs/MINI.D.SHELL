/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:09:23 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/24 15:05:39 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_cd(t_shell *shell, char *path)
{
	char	*new_path;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		shell->exit_status = 1;
		perror("cd");
		return (EXIT_FAILURE);
	}
	if (!path || !*path)
	{
		new_path = getenv("HOME");
		if (!new_path)
		{
			free(old_pwd);
			ft_putstr_fd("cd : HOME not set\n", 2);
			shell->exit_status = 1;
			return (1);
		}
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		new_path = getenv("OLDPWD");
		if (!new_path)
		{
			free(old_pwd);
			ft_putstr_fd("cd : OLDPWD not set\n", 2);
			shell->exit_status = 1;
			return (1);
		}
        printf("%s\n", new_path);
	}
    else 
        new_path = path;
}

/*
gerer: cd sans arguments (va au repertoire HOME)
cd - (va OLDPWD remonte au repertoire precedent)
cd chemin (vas au chemin precisee absolu ou relatif)

gestion des erreurs : -droits d accees
 - repertoire inexistant
 - chemin invalide
 - variable d environnement manquant
*/