#include "../include/minishell.h"

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
	if (ft_strncmp(content, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(content, ">>", 2) == 0)
		return (RR_RED);
	if (ft_strncmp(content, ">", 1) == 0)
		return (R_RED);
	if (ft_strncmp(content, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(content, "<", 1) == 0)
		return (L_RED);
	return (0);
}

int	ft_compute_token(t_token *before, char *new)
{
	if (is_redirect(new))
		return (is_redirect(new));
	if (is_redirect(before->content) == R_RED && !is_redirect(new))
		return (FIL);
	if (is_redirect(before->content) && !is_redirect(new))
		return (WORD);
	if (!is_redirect(before->content) && !is_redirect(new))
		return (SFX);
	return (WORD);
}

void	ft_add_token(char *content, t_command_line *command)
{
	t_token *current;
	t_token *new;

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