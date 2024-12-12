/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:48:03 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 20:53:31 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	printf ("fin ft expand\n");
	return (EXIT_SUCCESS);
}

char	*expand_var(char *input, t_shell *shell, t_token *current)
{
	t_expand_state	state;
	int				i;

	i = 0;
	state.in_quote = 0;
	state.result = ft_strdup("");
	if (!state.result)
		return (NULL); // gerer probleme printf au plus tot verifier invalid read size
	// if (ft_strcmp(input,"\"\"") || ft_strcmp(input, "''"))
	// 	return (ft_strdup("\0"));
	state.exit_status = shell->exit_status;
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
	if (state.result[0] == '\0')
		state.result = handle_empty_word(state.result, input, current->type);
	if (!state.result)
		return (NULL);
	printf("je test %s\n", state.result);
	return (state.result);
}
// if (state.result[0] == '\0' && current->type == WORD)
// {
// 	ft_free(state.result);
// 	state.result = ft_strdup("b*54w/afq8974d");
// 	if (!state.result)
// 		return (NULL);
// }
// else if (state.result[0] == '\0' && current->type == FILE_TOKEN)
// {
// 	ft_free(state.result);
// 	state.result = ft_strdup(input);
// 	if (!state.result)
// 		return (NULL);
// }

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

void	handle_expansion(char *input, int *i, t_expand_state *state,
		t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	int		len;

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
	(ft_free(var_name), ft_free(var_value), *i += len);
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

/*
$$ -> pid du shell // pas devoir gerer
$? -> statut de sortie
$0 -> nom du shell

gerer aussi les cas ou j export apres je dois expand a verifier?
*/
