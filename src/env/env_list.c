/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:49:34 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/06 23:16:44 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gc.h"
#include "../../include/minishell.h"

static char	*get_incremented_shlvl(const char *current_shlvl);
static void	initialize_minimal_env(t_shell *shell);

int	fill_env_list(t_shell *shell)
{
	int		i;
	t_env	*new;
	t_env	*current;
	char	*shlvl_value;

	i = 0;
	if (!shell->env || !shell->env[0])
	{
		initialize_minimal_env(shell);
		return (0);
	}
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "SHLVL=", 6) == 0)
		{
			shlvl_value = get_incremented_shlvl(shell->env[i] + 6);
			break ;
		}
		i++;
	}
	if (!shell->env[i])
		shlvl_value = ft_strdup("1");
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "SHLVL=", 6) == 0)
		{
			new = ft_malloc(sizeof(t_env));
			if (!new)
				return (-1);
			new->key = ft_strdup("SHLVL");
			new->value = ft_strdup(shlvl_value);
			new->next = NULL;
			ft_lock(new);
			ft_lock(new->key);
			ft_lock(new->value);
		}
		else
			new = create_env_node(shell->env[i]);
		if (!new)
			return (-1);
		if (!shell->head)
			shell->head = new;
		else
		{
			current = shell->head;
			while (current->next)
				current = current->next;
			current->next = new;
		}
		i++;
	}
	ft_free(shlvl_value);
	return (0);
}

t_env	*create_env_node(char *env_str)
{
	t_env	*new;
	int		sep_index;

	new = ft_malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	sep_index = ft_findchar(env_str, '=');
	if (sep_index == -1)
		return (ft_free(new), NULL);
	new->key = ft_substr(env_str, 0, sep_index);
	new->value = ft_substr(env_str, sep_index + 1, ft_strlen(env_str)
			- sep_index);
	if (!new->key || !new->value)
	{
		free_env_node(new);
		return (NULL);
	}
	ft_lock(new);
	ft_lock(new->key);
	ft_lock(new->value);
	new->next = NULL;
	return (new);
}

void	free_env_list(t_shell *shell)
{
	t_env	*current;
	t_env	*next;

	if (!shell || !shell->head)
		return ;
	current = shell->head;
	while (current)
	{
		next = current->next;
		free_env_node(current);
		current = next;
	}
	shell->head = NULL;
}

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->key)
		ft_free(node->key);
	if (node->value)
		ft_free(node->value);
	ft_free(node);
}

int	ft_findchar(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

static int	add_env_node(t_shell *shell, const char *key, const char *value)
{
	t_env	*node;
	t_env	*current;

	node = ft_malloc(sizeof(t_env));
	if (!node)
		return (1);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	if (!node->key || !node->value)
	{
		free_env_node(node);
		return (1);
	}
	ft_lock(node);
	ft_lock(node->key);
	ft_lock(node->value);
	if (!shell->head)
		shell->head = node;
	else
	{
		current = shell->head;
		while (current->next)
			current = current->next;
		current->next = node;
	}
	return (0);
}

static char	*get_incremented_shlvl(const char *current_shlvl)
{
	int		level;
	char	*new_shlvl;

	if (!current_shlvl || !*current_shlvl)
		level = 1;
	else
	{
		level = ft_atoi(current_shlvl);
		if (level < 0)
			level = 0;
		else if (level >= 999)
			level = 1;
		else
			level++;
	}
	new_shlvl = ft_itoa(level);
	return (new_shlvl);
}

static void	initialize_minimal_env(t_shell *shell)
{
	char	*cwd;

	shell->head = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("/");
	if (add_env_node(shell, "PWD", cwd) != 0)
		return ;
	ft_free(cwd);
	if (add_env_node(shell, "SHLVL", "1") != 0)
		return ;
	if (add_env_node(shell, "PATH", "/usr/local/bin:/usr/bin:/bin") != 0)
		return ;
	if (add_env_node(shell, "HOME", "/") != 0)
		return ;
	if (add_env_node(shell, "_", "/usr/bin/env") != 0)
		return ;
}
