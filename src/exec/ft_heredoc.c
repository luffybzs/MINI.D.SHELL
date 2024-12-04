/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:29:37 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/04 17:12:17 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_loop_heredoc(t_redir *current, t_shell *shell)
{
	char	*here;
	char	*tmp;

	(void)shell;
	/* ajout signaux*/
	// shell->sig_handler.mode = HEREDOC;
	// if (ft_setup_signal_handler(HEREDOC) == EXIT_FAILURE)
	// 	return;
	setup_interactive_signals();
	/* fin*/
	tmp = ft_strdup("");
	while (1)
	{
		here = readline(">");
		if (!here)
			break ;
		if (ft_strcmp(here, current->file) == 0)
			break ;
		// gere les $user
		tmp = ft_strjoin_free(tmp, here);
		ft_free(here);
		if (!tmp)
		{
			ft_putendl_fd("Mini.D.Shell : Error ft_malloc\n", 2);
			break ;
		}
		tmp = ft_strjoin_free(tmp, "\n");
		if (!tmp)
		{
			ft_putendl_fd("Mini.D.Shell : Error ft_malloc\n", 2);
			break ;
		}
	}
	current->heredoc = tmp;

	/*signaux fin*/
	setup_execution_signals();
}

int	ft_check_heredoc(t_shell *shell)
{
	t_exec *current;
	t_redir *current_redir;

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