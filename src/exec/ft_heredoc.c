/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:29:37 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/07 20:37:56 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_signal_status(t_redir *current)
{
	current->heredoc = NULL;
	g_signal_status = 100;
}

static int	check_delimiter(char *here, char *file)
{
	if (ft_strcmp(here, file) == 0)
	{
		ft_free(here);
		return (1);
	}
	return (0);
}

int	append_line(char **tmp, char *here, t_shell *shell)
{
	if (ft_strchr(here, '$'))
		here = handle_expand_here_doc(here, shell);
	*tmp = ft_strjoin_free(*tmp, here);
	ft_free(here);
	if (!*tmp)
	{
		ft_putendl_fd("Mini.D.Shell : Error ft_malloc\n", 2);
		return (0);
	}
	*tmp = ft_strjoin_free(*tmp, "\n");
	if (!*tmp)
	{
		ft_putendl_fd("Mini.D.Shell : Error ft_malloc\n", 2);
		return (0);
	}
	return (1);
}

void	ft_loop_heredoc(t_redir *current, t_shell *shell)
{
	char	*here;
	char	*tmp;

	tmp = ft_strdup("");
	if (!tmp)
		return ;
	while (1)
	{
		here = readline(">");
		if (g_signal_status != 100)
			return (handle_signal_status(current));
		if (!here)
		{
			ft_free(tmp);
			break ;
		}
		if (check_delimiter(here, current->file))
			break ;
		if (!append_line(&tmp, here, shell))
			break ;
	}
	current->heredoc = tmp;
}

int	ft_check_heredoc(t_shell *shell)
{
	t_exec	*current;
	t_redir	*current_redir;

	current = shell->first_exec;
	while (current)
	{
		if (current->redir)
		{
			current_redir = current->redir;
			while (current_redir)
			{
				if (current_redir->type == END_OF_FILE)
					ft_loop_heredoc(current_redir, shell);
				current_redir = current_redir->next;
			}
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
void	append_char_spe(char *str, char c)
{
	char	*new;
	int		len;

	if (!str)
		return ;
	len = ft_strlen(str);
	new = ft_malloc(len + 2);
	if (!new)
		return ;
	ft_strlcpy(new, str, len + 1);
	new[len] = c;
	new[len + 1] = '\0';
	ft_free(str);
	str = new;
}

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
	else if (c == '$')
		return (ft_itoa(shell->shell_pid));
	else if (c == '0')
		return (ft_strdup(shell->shell_name));
	return (NULL);
}

static void	handle_special_vars(char *str, int *i, t_shell *shell, char **exp)
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

static void	handle_simple_dollar(char **expanded)
{
	char	*new_expanded;

	new_expanded = ft_strjoin(*expanded, "$");
	if (new_expanded)
	{
		ft_free(*expanded);
		*expanded = new_expanded;
	}
}

static void	handle_var_expansion(char *str, int *i, t_shell *shell, char **exp)
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

static void	handle_exp_hd(char *str, int *i, t_shell *shell, char **expanded)
{
	(*i)++;
	if (!str[*i])
		return (handle_simple_dollar(expanded));
	if (str[*i] == '?' || str[*i] == '$' || str[*i] == '0')
		handle_special_vars(str, i, shell, expanded);
	else
		handle_var_expansion(str, i, shell, expanded);
}

static char	*join_char(char *expanded, char c)
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
