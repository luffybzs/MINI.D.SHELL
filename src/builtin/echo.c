/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:02:59 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/25 16:46:41 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_echo(t_token *cmd, t_shell *shell)
{
	t_token	*current;
	int		is_n;

	(void)shell;
	is_n = 0;
	current = cmd->next;
	if (current && ft_strcmp(current->content, "-n") == 0)
	{
		is_n = 1;
		if(!current->next)
			return (1); // gerer le bon code de retour
		current = current->next;
		while (ft_strcmp(current->content, "-n") == 0)
			current = current->next;
	}
	while (current)
	{
		ft_putstr_fd(current->content, 1); // remplacer par le futur fd
		if (current->next)
			ft_putchar_fd(' ', 1);
		current = current->next;
	}
	if (!is_n)
		ft_putchar_fd('\n', 1);
	return (0);
}