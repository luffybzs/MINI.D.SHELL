/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:44:10 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/02 14:46:38 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error_token(char *content)
{
	ft_putstr_fd("MINI.D.SHELL: « ", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd(" » ERROR INVALID TOKEN\n", 2);
}

void	ft_error_pide(char *content)
{
	ft_putstr_fd("MINI.D.SHELL: syntax error near unexpected token « ", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd(" »\n", 2);
}
void	ft_error_double_redir(char *content)
{
	ft_putstr_fd("MINI.D.SHELL: syntax error near unexpected token « ", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd(" »\n", 2);
}

void	ft_error_quote(void)
{
	ft_putstr_fd("MINI.D.SHELL: error open quote\n", 2);
}

void	ft_error_end_redir(void)
{
	ft_putstr_fd("MINI.D.SHELL: syntax error near unexpected token « ", 2);
	ft_putstr_fd("newline »\n", 2);
}