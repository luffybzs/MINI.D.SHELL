/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:02:59 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/20 12:19:31 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_echo(t_token *cmd, t_shell *shell)
{
	t_token *current;
	int is_n;
    int i;
	int fd; // temporaire avant de recuperer le fd
	(void)shell;
    
    fd = 1;
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
        	//if(current->content == "\"")
			//	handle_double_quote(shell,is_n,current,fd);
			i++;
		} //ajouter le cas ou la double quote
		 ft_putstr_fd(current->content, fd);
        if (current->next)
            ft_putchar_fd(' ',fd);
		current = current->next;
		i = 0;
	}
	if (!is_n)
		ft_putchar_fd('\n', fd);
	return (0);
}
void	handle_double_quote(t_shell *shell, int is_n, t_token *actual, int fd)
{
	int i;
	int is_double_quote;
	int is_simple_quote;

	t_token *current;
	(void) shell;
	i = 0;
	(void)is_n;
	current = actual;
	
	//current->content = ft_supp_quote();
	while (current->content[i])
	{
		if(current->content[i] == '"' )
			is_double_quote = 1;
		if(current->content[i] == '\'')
			is_simple_quote = 1;
		i++;
	}
	
	ft_putstr_fd(current->content,fd);

}