/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:29:13 by utilisateur       #+#    #+#             */
/*   Updated: 2024/11/15 15:33:04 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_add_cmd(char *command, t_command_line *line, int *i)
{
	int j;
    int check;
    char tmp;
	j = 0;
    check = 0;
	while (command[*i + j] && !ft_isspace(command[*i + j]) 
	&& !ft_isseparator(command[*i + j]))
	{
		if (command[*i + j] == '"' || command[*i + j] == '\'')
        {
            tmp = command[*i + j];            
			check = ft_next_char(command, command[*i + j], i, &j);
        }
		j++;
    }
    if (check == 1)
	    ft_add_token(ft_supp_quote(command,*i, &j, tmp),line);
    else
	    ft_add_token(ft_substr(command, *i,j), line);
	(*i) += j;

}

void ft_add_redirect(char *command,t_command_line *line, int *i)
{
	char *red;
	char c;
	int	 j;

	j = 0;
	c = command[*i];
	while (command[*i + j] == c)
		j++;
	red = malloc(sizeof(char) * (j + 1));
	if (!red)
		return ; 
	j = 0;
	while (command[*i + j] == c)
	{
		red[j] = command[*i + j];
		j++;
	}
	red[j] = '\0';
	(*i) += j;
	ft_add_token(red, line);
}