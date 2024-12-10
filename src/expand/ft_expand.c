/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:48:03 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/09 23:35:48 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// penser a initialiser dans la struccture shell le pid, le nom,
// et le code d exit

int	ft_expand(t_command_line *line, t_shell *shell)
{
	t_token	*current;
	char	*expanded;

	current = line->first;
	while (current)
	{
		expanded = expand_var(current->content, shell, current);
		if (expanded)
		{
			ft_free(current->content);
			current->content = expanded;
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

char	*expand_var(char *input, t_shell *shell, t_token *current)
{
	t_expand_state state;
	int i;

	i = 0;
	state.in_quote = 0;
	state.result = ft_strdup("");
	if (!state.result)
		return (NULL);
	state.exit_status = shell->exit_status;
	// recuperer le code d erreur plus tard lors de l exec ?
	i = 0;
	while (input[i])
	{
		if (handle_quotes(input[i], &state) == 1)
			i++;
		else if (input[i] == '$' && state.in_quote != 2 && current->type != 19)
			handle_expansion(input, &i, &state, shell);
		else
			append_char(&state.result, input[i++]);
	}
	return (state.result);
}

/*
state in quote :
0 : pas de quote
1 : double quote
2 : single quote
*/

int	handle_quotes(char c, t_expand_state *state) 
{
	if (c == '"' && state->in_quote != 2)
	{
		if (state->in_quote == 1)
			state->in_quote = 0;
		else
			state->in_quote = 1;
		return (1);
	}
	else if (c == '\'' && state->in_quote != 1)
	{
		if (state->in_quote == 2)
			state->in_quote = 0;
		else
			state->in_quote = 2;
		return (1);
	}
	return (0);
}

void	handle_expansion(char *input,int *i,t_expand_state *state,t_shell *shell)
{
	char *var_name;
	char *var_value;
	int len;

	(*i)++;
	if (!input[*i])
	{
		append_char(&state->result, '$');
		return ;
	}
	if (handle_special_var(input[*i], i, state, shell))
		return ;
	len = get_var_name_length(input + *i);
	if (len == 0)
	{
		append_char(&state->result, '$');
		return ;
	}
	var_name = ft_substr(input, *i, len);
	if (!var_name)
		return ;
	var_value = get_env_value(var_name, shell);
	if (var_value)
		append_string(&state->result, var_value);
	(ft_free(var_name),ft_free(var_value),*i += len);
}

int	get_var_name_length(const char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
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
	else if (c == '$')
	{
		tmp = ft_itoa(shell->shell_pid);
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

/*
$$ -> pid du shell
$? -> statut de sortie
$0 -> nom du shell

gerer aussi les cas ou j export apres je dois expand a verifier?
*/
