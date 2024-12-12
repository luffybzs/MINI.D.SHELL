/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fonction_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:12:19 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/12 15:54:11 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_cpy_env(char *key, char *value)
{
	char	*res;

	res = ft_strjoin(key, "=");
	if (!res)
		return (NULL);
	res = ft_strjoin_free(res, value);
	if (!res)
		return (NULL);
	return (res);
}

char	**ft_lst_strdup(t_shell *shell)
{
	t_env	*current;
	char	**env_cpy;
	int		len;
	int		i;

	i = 0;
	len = ft_len_env(shell);
	if (len == 0)
		return (NULL);
	env_cpy = ft_malloc(sizeof(char *) * (len + 1));
	if (!env_cpy)
		return (NULL);
	current = shell->head;
	while (current)
	{
		env_cpy[i] = ft_cpy_env(current->key, current->value);
		if (!env_cpy[i])
			return (NULL);
		i++;
		current = current->next;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

int	ft_len_env(t_shell *shell)
{
	t_env	*current;
	int		i;

	i = 0;
	current = shell->head;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char	**ft_putflag(char **cmd)
{
	char	**res;
	int		i;

	if (!cmd)
		return (NULL);
	i = ft_strlen_2d(cmd);
	res = ft_malloc(sizeof(char *) * (i + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		res[i] = ft_strdup(cmd[i]);
		if (!res[i])
			return (NULL);
		i++;
	}
	res[i] = ft_strdup("--color");
	if (!res[i])
		return (NULL);
	res[i + 1] = NULL;
	return (res);
}

int	ft_cmp_flag(char *cmd)
{
	if (ft_strcmp(cmd, "ls") == 0)
		return (EXIT_SUCCESS);
	else if (ft_strcmp(cmd, "grep") == 0)
		return (EXIT_SUCCESS);
	else if (ft_strcmp(cmd, "diff") == 0)
		return (EXIT_SUCCESS);
	else if (ft_strcmp(cmd, "dir") == 0 || ft_strcmp(cmd, "vdir") == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
