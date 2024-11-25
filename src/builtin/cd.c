/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:09:23 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/25 11:10:23 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static char	*get_env_for_cd(t_env *head, char *key) // cherche la clee
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

static t_env	*update_or_create_env(t_env *head, char *key, char *value)
{ // remplace l ancienne valeur si existante sinon la cree
	t_env	*current;

	current = head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (head);
		}
		current = current->next;
	}
	current = malloc(sizeof(t_env));
	if (!current)
		return (NULL);
	current->key = ft_strdup(key);
	current->value = ft_strdup(value);
	current->next = head;
	return (current);
}

static int	update_pwd_env(t_shell *shell, char *old_pwd)
{//mise a jour des variables en tete de liste env
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (1);
	shell->head = update_or_create_env(shell->head, "PWD", current_pwd);
	if (!shell->head)
	{
		free(current_pwd);
		return (1);
	}
	shell->head = update_or_create_env(shell->head, "OLDPWD", old_pwd);
	if (!shell->head)
	{
		free(current_pwd);
		return (1);
	}
	free(current_pwd);
	return (0);
}

static void	handle_cd_error(char *path, t_shell *shell)
{//finir d associer les differnete erreurs
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

int	ft_cd(t_shell *shell)
{
	char	*path;
	char	*old_pwd;
	t_token	*current;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	current = shell->command->first;
	while (current && current->type == WORD)
		current = current->next;
	if (!current)
	{
		path = get_env_for_cd(shell->head, "HOME");
		if (!path)
		{
			ft_putstr_fd(shell->shell_name, 2);
			ft_putendl_fd(": cd: HOME not set", 2);
			free(old_pwd);
			shell->exit_status = 1;
			return (1);
		}
	}
	else
		path = current->content;
	if (chdir(path) != 0)
	{
		handle_cd_error(path, shell);
		free(old_pwd);
		return (1);
	}
	if (update_pwd_env(shell, old_pwd))
	{
		free(old_pwd);
		shell->exit_status = 1;
		return (1);
	}
	free(old_pwd);
	shell->exit_status = 0;
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