/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:02:59 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/19 12:12:37 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_echo(t_token *cmd, t_shell *shell)
{
	t_token *current;
	int is_n;
    int fd;
	(void)shell;
    
    fd = 1;
	is_n = 0;
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
        // if(current->content == "")
			//ajouter le cas ou la double quote
        ft_putstr_fd(current->content, fd);
        if (current->next)
            ft_putchar_fd(' ',fd);
		current = current->next;
	}
	if (!is_n)
		ft_putchar_fd('\n', fd);
	//remplacer 1 par fd apres avoir gerer redirection
	return (0);
}
