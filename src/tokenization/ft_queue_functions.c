#include "../../include/minishell.h"

t_command_line	*ft_init_queue(void)
{
	t_command_line	*list;

	list = malloc(sizeof(t_command_line));
	if (!list)
		return (NULL);
	list->first = NULL;
	return (list);
}

int	is_redirect(char *content)
{
	if (ft_strncmp(content, "||", 2) == 0) /*	error	*/
		return (-1);
	if (ft_strncmp(content, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(content, ">>>", 3) == 0) /*	error	*/
		return (-1);
	if (ft_strncmp(content, ">>", 2) == 0)
		return (RR_RED);
	if (ft_strncmp(content, ">", 1) == 0)
		return (R_RED);
	if (ft_strncmp(content, "<<<", 3) == 0) /*	error	*/
		return (-1);
	if (ft_strncmp(content, "<<", 2) == 0)
		return (LL_RED);
	if (ft_strncmp(content, "<", 1) == 0)
		return (L_RED);
	return (0);
}

int	ft_compute_token(t_token *before, char *new)
{
	if (is_redirect(new))
		return (is_redirect(new));
	if (is_redirect(before->content) == PIPE && !is_redirect(new))
		return (WORD);
	if (!is_redirect(before->content) && !is_redirect(new))
		return (SFX);
	if (is_redirect(before->content) == LL_RED && !is_redirect(new))
		return (END_OF_FILE);
	return (FILE);
}

void	ft_add_token(char *content, t_command_line *command)
{
	t_token	*current;
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	current = command->first;
	new->next = NULL;
	new->content = content;
	new->type = WORD;
	if (!command->first)
	{
		new->type = is_redirect(content);
		command->first = new;
	}
	else
	{
		while (current->next)
			current = current->next;
		new->type = ft_compute_token(current, content);
		current->next = new;
	}
}
t_token	*ft_lstlast_mini(t_command_line *lst)
{
	t_token *tmp;

	if (!lst)
		return (NULL);
	tmp = lst->first;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}