/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:31:33 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/24 02:32:05 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exec_line	*ft_init_queue_exec(void)
{
	t_exec_line	*list;

	list = malloc(sizeof(t_exec_line));
	if (!list)
		return (NULL);
	list->first = NULL;
	return (list);
}
int ft_nb_cmd(t_token *current)
{
	int nb;
	nb = 0;
	while (current)
	{
		if (current->type == WORD || current->type == SFX)
			nb++;
		if (current->type == PIPE)
			break;
		current = current->next;
	}
	return (nb);
}

void ft_add_tab_cmd(t_exec_line *line, char **tab)
{
	t_exec *current;
	t_exec *new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return ;
	current = line->first;
	new->cmd = tab;
	new->next = NULL;
	if (!current)
		line->first = new;
	else 
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}
void ft_cpy_cmd(t_exec_line *line, t_shell *shell)
{
	t_token *current;
	int len;
	char **tab;
	int i;

	current = shell->command->first;
	while (current)
	{
		if(current->type == WORD)
		{
			i = 0;
			len = ft_nb_cmd(current);
			tab = malloc(sizeof(char *) * (len + 1));
			if (!tab)
				return ;
			while (current && current->type != PIPE)
			{
				if (current->type == WORD || current->type == SFX)
					{
						tab[i] = ft_strdup(current->content);
						i++;
					}
				current = current->next;
			}
			tab[i] = NULL;
			ft_add_tab_cmd(line,tab);	
		}
		if (current)
			current = current->next;
	}	
}
void ft_display_exec(t_exec_line *line)
{
	t_exec *current;
	int i;
	current = line->first;
	while (current)
	{
		i = 0;
		while (current->cmd[i])
		{
			printf("[%s] ----------> [%d] = etage de la cmd\n", current->cmd[i], i);
			i++;
		}
		current = current->next;
	}
}



int ft_start_cmd(t_shell *shell)
{
	t_exec_line *line;
	line = ft_init_queue_exec();
	ft_cpy_cmd(line,shell);
	ft_display_exec(line);
	return (EXIT_SUCCESS);
}

