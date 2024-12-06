/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fonction_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:12:19 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/06 15:30:52 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_cpy_env(char *key, char *value)
{
	char	*res;

	res = ft_strdup(key);
	if (!res)
		return (NULL);
	res = ft_strjoin_free(res, "=");
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
