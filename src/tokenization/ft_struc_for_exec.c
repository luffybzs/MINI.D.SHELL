/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struc_for_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:01:35 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/28 17:23:08 by wdaoudi-         ###   ########.fr       */
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
		if (current->type == FILE || current->type == END_OF_FILE)
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
			if (type == PIPE)
				ft_init_lst_redir(redir, type, current->content);
			else
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
	printf("\nFIN DE LA DEUXIME LIST DE FILE\n\n");
}

void ft_cpy_cmd(t_token *current, t_exec *exec_current)
{
	int len;
	char **tab;
	int i;

	i = 0;
	len = ft_nb_cmd(current);
	tab = malloc(sizeof(char *) * (len + 1));
	while (current && current->type != PIPE)
	{
		if (current->type == WORD)
		{
			tab[i] = current->content;
			i++;
		}
		current = current->next;
	}
	tab[i] = NULL;
	exec_current->cmd = tab;
}

int ft_struc_for_exec(t_shell *shell)
{
	t_token *current;
	t_exec *first_cmd;
	t_exec *buff_exec;
	t_exec *new_cmd;
	t_redir *file;
	t_redir *buff;
	
	first_cmd = NULL;
	current = shell->command->first;
	while (current)
	{
		new_cmd = malloc(sizeof(t_exec));
		ft_bzero(new_cmd, sizeof(t_exec));
		ft_cpy_cmd(current, new_cmd);
		while (current && current->type != PIPE)
		{
			if (ft_is_file(current->type) != -1)
			{
				file = malloc(sizeof(t_redir));
				file->file = current->next->content;
				file->type = ft_is_file(current->type);
				file->next = NULL;
				if (new_cmd->redir == NULL)
					new_cmd->redir = file;
				else
				{
					buff = new_cmd->redir;
					while (buff->next)
						buff = buff->next;
					buff->next = file;
				}
			}
			current = current->next;
		}
		if (first_cmd == NULL)
			first_cmd = new_cmd;
		else
		{
			buff_exec = first_cmd;
			while (buff_exec->next)
				buff_exec = buff_exec->next;
			buff_exec->next = new_cmd;
		}
		if (current)
			current = current->next;
	}
	shell->first_exec = first_cmd;
	return (EXIT_SUCCESS);
}
