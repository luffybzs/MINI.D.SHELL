/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struc_for_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:01:35 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/24 01:51:02 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redir_line	*ft_init_queue_redir(void)
{
	t_redir_line	*list;

	list = malloc(sizeof(t_redir_line));
	if (!list)
		return (NULL);
	list->head = NULL;
	return (list);
}

void ft_init_lst_redir(t_redir_line *lst, int type, char *file)
{
	t_redir *current;
	t_redir *new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	current = lst->head;
	new->file = file;
	new->type = type;
	new->next = NULL;
	if (!current)
		lst->head = new;
	else 
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}
int ft_check_file(t_shell *shell)
{
	t_token *current;

	current = shell->command->first;
	while (current)
	{
		if (current->type == FILE)
			return (EXIT_SUCCESS);
		current = current->next;
	}
	return (EXIT_FAILURE);
}
void  ft_cpy_file(t_shell *shell, t_redir_line *redir)
{
	t_token *current;
	int type;
	current = shell->command->first;
	while (current->next)
	{
		type = ft_is_file(current->type);
		if (type != -1)
		{
			ft_init_lst_redir(redir, type, current->next->content);
		}
		current = current->next;
	}
}
void ft_display_file(t_redir_line *lst)
{
	t_redir *current;

	current = lst->head;

	while (current)
	{
		printf("file [%s] ---> type [%d]\n", current->file, current->type);
		current = current->next;
	}
}

int ft_struc_for_exec(t_shell *shell)
{
	t_redir_line *lst;
	
	if (ft_check_file(shell) == EXIT_SUCCESS)
		{
			lst = ft_init_queue_redir();
			ft_cpy_file(shell, lst);
		}
	if (ft_start_cmd(shell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}
//	ft_display_file(lst);