/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fonction_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:07:26 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/12 16:01:26 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exec_line	*ft_init_queue_exec(void)
{
	t_exec_line	*list;

	list = ft_malloc(sizeof(t_exec_line));
	if (!list)
		return (NULL);
	list->first = NULL;
	return (list);
}

int	ft_nb_cmd(t_token *current)
{
	int	nb;

	nb = 0;
	while (current)
	{
		if (current->type == WORD || current->type == SFX)
			nb++;
		if (current->type == PIPE)
			break ;
		current = current->next;
	}
	return (nb);
}

int	ft_check_open_quote(char *prompt)
{
	int		i;
	char	quote;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' || prompt[i] == '"')
		{
			quote = prompt[i++];
			while (prompt[i] && prompt[i] != quote)
				i++;
			if (!prompt[i])
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

char	*ft_print_color(int i)
{
	static char	str[100000];
	int			r;
	int			g;
	int			b;

	r = 255 - i;
	g = 0 + i;
	b = 0;
	ft_s_printf(str, "\033[38;2;%d;%d;%dm%s\033[0m", r, g, b, "Mini.D.Shell-> ");
	return (str);
}

void	ft_fill_data(t_shell *shell, char **av)
{
	shell->shell_name = ft_strdup(av[0]);
	shell->exit_status = 0;
	g_signal_status = 0;
	shell->previous_pipe_fd = -1;
}
