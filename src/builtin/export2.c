/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:27:25 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 16:31:02 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	is_name_ok(char *str, t_shell *shell)
{
	int	i;

	i = 0;
	if (check_empty_name(str, shell))
		return (1);
	if (check_first_char(str, shell))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
		{
			print_identifier_error(str, shell);
			return (1);
		}
		i++;
	}
	return (0);
}

t_env	*ft_find_env(t_shell *shell, char *key)
{
	t_env	*current;
	size_t	key_len;
	char	*equal_sign;

	if (!key || !shell || !shell->head)
		return (NULL);
	equal_sign = ft_strchr(key, '=');
	if (equal_sign)
		key_len = (size_t)(equal_sign - key);
	else
		key_len = ft_strlen(key);
	current = shell->head;
	while (current)
	{
		if (ft_strlen(current->key) == key_len && !ft_strncmp(key, current->key,
				key_len))
			return (current);
		current = current->next;
	}
	return (NULL);
}

char	*get_value(char *str)
{
	char	*part;

	part = ft_strchr(str, '=');
	if (!part)
		return (NULL);
	if (*(part + 1) == '\0')
		return (ft_strdup(""));
	return (ft_strdup(part + 1));
}

t_env	*init_env_node(void)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

int	set_key_value(t_env *new, char *str, char *equal_sign)
{
	char	*new_key;
	char	*new_value;

	if (!equal_sign)
	{
		new_key = ft_strdup(str);
		new_value = ft_strdup("");
	}
	else
	{
		new_key = ft_substr(str, 0, equal_sign - str);
		if (*(equal_sign + 1))
			new_value = ft_strdup(equal_sign + 1);
		else
			new_value = ft_strdup("");
	}
	if (!new_key || !new_value)
	{
		ft_free(new_key);
		ft_free(new_value);
		return (0);
	}
	new->key = new_key;
	new->value = new_value;
	return (1);
}
