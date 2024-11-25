/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:31:33 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/25 17:55:14 by wdaoudi-         ###   ########.fr       */
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
char **ft_add_to_tab(t_token *current, char **tab)
{
	int i;

	i = 0;
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
	return (tab);
}


void ft_cpy_cmd(t_exec_line *line, t_shell *shell)
{
	t_token *current;
	int len;
	char **tab;

	current = shell->command->first;
	while (current)
	{
		if(current->type == WORD)
		{
			len = ft_nb_cmd(current);
			tab = malloc(sizeof(char *) * (len + 1));
			if (!tab)
				return ;
			tab = ft_add_to_tab(current, tab);
			while (current && current->type != PIPE)
				current = current->next;
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
	printf("\nFIN DE LA LIST DE EXEC\n");
}
int ft_check_word(t_shell *shell)
{
	t_token *current;

	current = shell->command->first;
	while (current)
	{
		if (current->type == WORD)
			return (EXIT_SUCCESS);
		current = current->next;
	}
	return (EXIT_FAILURE);
}


int ft_start_cmd(t_shell *shell)
{
	t_exec_line *line;
	
	if (ft_check_word(shell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	line = ft_init_queue_exec();
	shell->exec_line = line;
	ft_cpy_cmd(line,shell);
	ft_display_exec(line);
	return (EXIT_SUCCESS);
}

