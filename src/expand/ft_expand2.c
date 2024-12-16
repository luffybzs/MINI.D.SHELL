/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:04:59 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/16 13:55:17 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_empty_word(t_expand_state *state, t_token *current, char *input)
{
	(void)current;
	ft_free(state->result);
	if (input)
	{
		if ((current->type == 0 || current->type == 1) && !ft_strncmp_spe(input,
				"$", 1))
		{
			state->result = ft_strdup(input);
			current->type = -3;
		}
		else if (current->type == 20)
			state->result = ft_strdup(input);
		else
			state->result = ft_strdup("\0");
	}
	else
		state->result = ft_strdup("\0");
	return (state->result);
}

size_t	ft_strncmp_spe(char *str1, char *str2, size_t n)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (str1[i] == ' ')
		i++;
	while (j < n && str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
		j++;
	}
	if (j < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	}
	return (0);
}

void	append_char(char **str, char c)
{
	char	*new;
	int		len;

	if (!*str)
		return ;
	len = ft_strlen(*str);
	new = ft_malloc(len + 2);
	if (!new)
		return ;
	ft_strlcpy(new, *str, len + 1);
	new[len] = c;
	new[len + 1] = '\0';
	ft_free(*str);
	*str = new;
}

void	append_string(char **dst, const char *src)
{
	char	*new;

	if (!*dst || !src)
		return ;
	new = ft_strjoin(*dst, src);
	if (!new)
		return ;
	ft_free(*dst);
	*dst = new;
}

char	*get_env_value(const char *name, t_shell *shell)
{
	char	*full_var;
	t_env	*env;

	env = shell->head;
	while (env)
	{
		full_var = env->key;
		if (ft_strcmp(full_var, name) == 0 && env->value[0] != 0)
		{
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}
