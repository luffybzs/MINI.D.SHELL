/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:50:08 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 15:51:33 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	append_string_spe(char *dst, char *src)
{
	char	*new;

	if (!dst || !src)
		return ;
	new = ft_strjoin(dst, src);
	if (!new)
		return ;
	ft_free(dst);
	dst = new;
}

char	*get_special_value(char c, t_shell *shell)
{
	if (c == '?')
		return (ft_itoa(shell->exit_status));
	else if (c == '0')
		return (ft_strdup(shell->shell_name));
	return (NULL);
}

void	handle_special_vars(char *str, int *i, t_shell *shell, char **exp)
{
	char	*tmp;
	char	*new_exp;

	tmp = get_special_value(str[*i], shell);
	if (!tmp)
		return ;
	(*i)++;
	new_exp = ft_strjoin(*exp, tmp);
	ft_free(tmp);
	if (new_exp)
	{
		ft_free(*exp);
		*exp = new_exp;
	}
}

void	handle_simple_dollar(char **expanded)
{
	char	*new_expanded;

	new_expanded = ft_strjoin(*expanded, "$");
	if (new_expanded)
	{
		ft_free(*expanded);
		*expanded = new_expanded;
	}
}

void	handle_var_expansion(char *str, int *i, t_shell *shell, char **exp)
{
	char	*var_name;
	char	*var_value;
	char	*new_exp;
	int		len;

	len = get_var_name_length(str + *i);
	if (len == 0)
		return (handle_simple_dollar(exp));
	var_name = ft_substr(str, *i, len);
	if (!var_name)
		return ;
	var_value = get_env_value(var_name, shell);
	if (var_value)
	{
		new_exp = ft_strjoin(*exp, var_value);
		if (new_exp)
		{
			ft_free(*exp);
			*exp = new_exp;
		}
		ft_free(var_value);
	}
	ft_free(var_name);
	*i += len;
}
