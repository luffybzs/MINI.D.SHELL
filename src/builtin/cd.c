/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:09:23 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/06 14:35:35 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static char	*get_env_for_cd(t_env *head, char *key) // cherche la clee
{
	t_env *current;

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
{
	t_env	*current;

	// remplace l ancienne valeur si existante sinon la cree
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

static int	update_pwd_env(t_shell *shell, char *old_pwd)
{
	char	*current_pwd;

	// mise a jour des variables en tete de liste env
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

static void	handle_cd_error(char *path, t_shell *shell)
{
	// finir d associer les differnete erreurs
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

static int handle_cd_no_args(t_shell *shell, char **path)
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

static int handle_cd_args(t_exec *current, t_shell *shell)
{
    if (current->cmd[1] && current->cmd[2])
    {
        ft_putstr_fd(shell->shell_name, 2);
        ft_putstr_fd(": cd: too many arguments\n", 2);
        shell->exit_status = 1;
        return (1);
    }
    return (0);
}

static int execute_cd(char *path, char *old_pwd, t_shell *shell)
{
    if (chdir(path) != 0)
    {
        handle_cd_error(path, shell);
        return (1);
    }
    if (update_pwd_env(shell, old_pwd))
    {
        shell->exit_status = 1;
        return (1);
    }
    shell->exit_status = 0;
    return (0);
}

int ft_cd(t_exec *current, t_shell *shell)
{
    char    *path;
    char    *old_pwd;
    int     ret;

    old_pwd = getcwd(NULL, 0);
    if (!old_pwd)
        return (shell->exit_status = 1, 1);
    if (handle_cd_args(current, shell))
        return (ft_free(old_pwd), 1);
    if (!current->cmd[1])
    {
        if (handle_cd_no_args(shell, &path))
            return (ft_free(old_pwd), 1);
    }
    else
        path = current->cmd[1];
    ret = execute_cd(path, old_pwd, shell);
    ft_free(old_pwd);
    return (ret);
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