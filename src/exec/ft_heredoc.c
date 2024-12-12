/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:29:37 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/12 15:50:43 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_delimiter(char *here, char *file, t_shell *shell)
{
	char	res[100000];
	char	*st;
	char	*end;

	end = "delimited by end-of-file (wanted ";
	st = "Mini.D.Shell: warning: here-document at line";
	if (!here)
	{
		ft_s_printf(res, RED "%s %d %s`%s')" WHITE, st, shell->nb_line, end,
			file);
		ft_free(here);
		ft_putendl_fd(res, 2);
		return (1);
	}
	if (ft_strcmp(here, file) == 0)
	{
		ft_free(here);
		return (1);
	}
	return (0);
}

int	append_line(char **tmp, char *here, t_shell *shell, t_redir *current)
{
	(void)current;
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

int	ft_loop_heredoc(t_redir *current, t_shell *shell)
{
	char	*here;
	char	*tmp;

	tmp = ft_strdup("");
	if (!tmp)
		return (EXIT_FAILURE);
	while (1)
	{
		here = readline(">");
		if (check_delimiter(here, current->file, shell) || !append_line(&tmp,
				here, shell, current))
			break ;
		if (g_signal_status != 0)
			return (EXIT_FAILURE);
		if (!here)
		{
			ft_free(tmp);
			break ;
		}
	}
	current->heredoc = tmp;
	return (EXIT_SUCCESS);
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
					if (ft_loop_heredoc(current_redir, shell) == EXIT_FAILURE)
						return (EXIT_FAILURE);
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
