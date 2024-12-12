/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:04:59 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 16:22:26 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_empty_word(char *result, char *input, int type)
{
	ft_free(result);
	if (type == WORD)
		result = ft_strdup("b*54w/afq8974d");
	else if (type == FILE_TOKEN)
		result = ft_strdup(input);
	return (result);
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

int	handle_special_var(char c, int *i, t_expand_state *state, t_shell *shell)
{
	char	*tmp;

	if (c == '?')
	{
		tmp = ft_itoa(shell->exit_status);
		append_string(&state->result, tmp);
		ft_free(tmp);
		(*i)++;
		return (1);
	}
	else if (c == '0')
	{
		append_string(&state->result, shell->shell_name);
		(*i)++;
		return (1);
	}
	return (0);
}
