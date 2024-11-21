/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:02:59 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/21 12:22:18 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_echo(t_token *cmd, t_shell *shell)
{
	t_token	*current;
	int		is_n;
	int		i;

	(void)shell;
	is_n = 0;
	i = 0;
	current = cmd->next;
	if (current && ft_strcmp(current->content, "-n") == 0)
	{
		is_n = 1;
		while (ft_strcmp(current->content, "-n") == 0)
			current = current->next;
		current = current->next;
	}
	while (current)
	{
		while (current->content[i])
		{
			if (current->content[i] == '"' || current->content[i] == '\'')
			{
				//handle_double_quote(shell, is_n, current->content, i);
				break ;
			}
			i++;
		} // ajouter le cas ou la double quote
		//  ft_putstr_fd(current->content, 1);
		if (current->next)
			ft_putchar_fd(' ', 1);
		current = current->next;
		i = 0;
	}
	if (!is_n)
		ft_putchar_fd('\n', 1);
	return (0);
}
/*
void	handle_double_quote(t_shell *shell, int is_n, char *current, int i)
{
	int is_double_quote;
	int is_simple_quote;
	char *word;
	(void)shell;

	if (current[i] == '"')
		is_double_quote = 1;
	if (current[i] == '\'')
		is_simple_quote = 1;
	word = ft_supp_quote2(current, current[i], i);
	printf("%s", word);
	// current->content = ft_supp_quote();
	if(!is_n)
		ft_putchar_fd('\n',1);
	// ft_putstr_fd(current->content,1);
}
*/