/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:58:44 by utilisateur       #+#    #+#             */
/*   Updated: 2024/11/15 19:34:45 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"


int  ft_next_char(char *str, char c, int *i , int *j)
{
    (*j)++;    
	while (str[*i + *j] != c)
		(*j)++;
    if (str[*i + *j] == c)
        return (1);
    return (0);
}

void	ft_skip_spaces(char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
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

int ft_len_word(char *command, int i, char c)
{
    int len;
	int bool;
    len = 0;
	while (command[i + len] && command[i + len] != c)
		len++;
	bool = 1;
	while (command[i + len])
	{
		if (command[i + len] && command[i + len] == c) 
			{
				while (command[i + len] && command[i + len] != c)
				{
					len++;		
				}
			}
			if (ft_isspace(command[i + len] && bool % 2 == 0 ))
				break;
			bool++;
		len++;
	}
    return (len);
}

// int ft_find_len_for_quote(char *cmd, int i, char c)
// {

// 	int len;
// 	len = 0;
// 	while (cmd[i + len])
// 	{
// 		while(cmd[i + len] && cmd[i + len] != c)
// 			len++;
// 		if  (ft_isspace(cmd[i + len]) && !ft_isspace(cmd[i + len + 1]))
// 			break;
// 		len++;
// 	}
// 	return (len);
// }

char *ft_supp_quote(char *command, int i, int *j, char c)
{
    char *word;
    int len;
    int tmp;
    tmp = 0;
    len = ft_len_word(command, i,c);
	*j = len + 1;
    word = malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    while(len) 
    {
        if (command[i] == c)
            i++;
        else
        {
            word[tmp] = command[i];
            tmp++;
            i++;
        } 
		len--;
    }
    word[tmp] = '\0';
    return (word);   
}


