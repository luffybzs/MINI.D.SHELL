/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:48:03 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/20 17:52:12 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_expand(t_command_line *line, t_shell *shell)
{
	t_token	*current;
	int		i;

	current = line->first;
	while (current)
	{
		i = 0;
		if (ft_find_dollar(current->content, &i) == 1 && ft_state_quote(current->content) != 2)
		{
			current->content = expand_var(current->content, &i, shell);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_find_dollar(char *content, int *i)
{
	while (content[*i])
	{
		if (content[*i] == '$')
			return (1);
		(*i)++;
	}
	return (0);
}

char	*expand_var(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;

	(*i)++;
	var_name = get_var_name(str + *i);
	if (!var_name)
		return (NULL);
	var_value = get_var_value(var_name, shell);
	(*i) += ft_strlen(var_name);
	free(var_name);
	return (var_value);
}

char	*get_var_name(char *content)
{
	int		len;
	char	*var_name;

	len = get_var_len(content);
	if (len == 0)
		return (NULL);
	var_name = ft_substr(content, 0, len);
	return (var_name);
}

int	get_var_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1); // creer une valeur dans la liste s_shell avec le code erreur qui printera
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
	}
	return (i);
}

char	*get_var_value(char *var_name, t_shell *shell)
{
	char	*env_value;
	int		i;
	size_t	var_len;

	if (!var_name)
		return (NULL);
	var_len = ft_strlen(var_name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var_name, var_len) == 0
			&& shell->env[i][var_len] == '=')
		{
			env_value = ft_strdup(shell->env[i] + var_len + 1);
			return (env_value);
		}
		i++;
	}
	return (ft_strdup(""));
}

int ft_state_quote(char *str)
{
    int i = 0;
    int state = 0;

    while (str[i])
    {
        if(str[i] == '"' && state == 0)
            state = 1;
        else if (str[i] == '\'' && state == 0)
            state = 2;
        i ++;
    }
    return (state);
}
