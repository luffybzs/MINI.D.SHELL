/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:09:23 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 16:53:14 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

char	*get_env_for_cd(t_env *head, char *key)
{
	t_env	*current;

	if (!head || !key)
		return (NULL);
	current = head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

t_env	*update_or_create_env(t_env *head, char *key, char *value)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			ft_free(current->value);
			current->value = ft_strdup(value);
			return (head);
		}
		current = current->next;
	}
	current = ft_malloc(sizeof(t_env));
	if (!current)
		return (NULL);
	current->key = ft_strdup(key);
	current->value = ft_strdup(value);
	current->next = head;
	return (current);
}

int	update_pwd_env(t_shell *shell, char *old_pwd)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (1);
	shell->head = update_or_create_env(shell->head, "PWD", current_pwd);
	if (!shell->head)
	{
		ft_free(current_pwd);
		return (1);
	}
	shell->head = update_or_create_env(shell->head, "OLDPWD", old_pwd);
	if (!shell->head)
	{
		ft_free(current_pwd);
		return (1);
	}
	ft_free(current_pwd);
	return (0);
}

void	handle_cd_error(char *path, t_shell *shell)
{
	ft_putstr_fd(shell->shell_name, 2);
	ft_putstr_fd(": cd: ", 2);
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else if (access(path, R_OK) == -1)
	{
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	else
	{
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Not a directory", 2);
	}
	shell->exit_status = 1;
}

int	handle_cd_no_args(t_shell *shell, char **path)
{
	*path = get_env_for_cd(shell->head, "HOME");
	if (!*path)
	{
		ft_putstr_fd(shell->shell_name, 2);
		ft_putendl_fd(": cd: HOME not set", 2);
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

/*
gerer: cd sans arguments (va au repertoire HOME)
cd - (va OLDPWD remonte au repertoire precedent)
cd chemin (vas au chemin precisee absolu ou relatif)

gestion des erreurs :
 - droits d accees
 - repertoire inexistant
 - chemin invalide
 - variable d environnement manquant
*/