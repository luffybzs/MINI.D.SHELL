/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:31:33 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/28 17:21:16 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


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
				if (!tab[i])
					return (NULL);
				i++;
			}
			current = current->next;
	}
	tab[i] = NULL;
	return (tab);
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


// int ft_start_cmd(t)
// {
// 	t_exec_line *line;
	
// 	if (ft_check_word(shell) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	line = ft_init_queue_exec();
// 	shell->exec_line = line;
// 	ft_cpy_cmd(line,shell);
// 	ft_display_exec(line);
// 	return (EXIT_SUCCESS);
// }

