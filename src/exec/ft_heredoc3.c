/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:51:04 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 15:51:23 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_exp_hd(char *str, int *i, t_shell *shell, char **expanded)
{
	(*i)++;
	if (!str[*i])
		return (handle_simple_dollar(expanded));
	if (str[*i] == '?' || str[*i] == '0')
		handle_special_vars(str, i, shell, expanded);
	else
		handle_var_expansion(str, i, shell, expanded);
}

char	*join_char(char *expanded, char c)
{
	char	current[2];
	char	*new_expanded;

	current[0] = c;
	current[1] = '\0';
	new_expanded = ft_strjoin(expanded, current);
	if (new_expanded)
	{
		ft_free(expanded);
		return (new_expanded);
	}
	return (NULL);
}

char	*handle_expand_here_doc(char *str, t_shell *shell)
{
	char	*expanded;
	int		i;

	i = 0;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
			handle_exp_hd(str, &i, shell, &expanded);
		else
			expanded = join_char(expanded, str[i++]);
		if (!expanded)
			return (NULL);
	}
	return (expanded);
}
