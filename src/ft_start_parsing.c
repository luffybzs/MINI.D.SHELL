/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:46:26 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/12 08:43:41 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_open_quote(char *prompt)
{
	int		i;
	char	c;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' || prompt[i] == '"')
		{
			c = prompt[i++];
			while (prompt[i] && prompt[i] != c)
				i++;
			if (!prompt)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	ft_skip_spaces(char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}

void ft_next_char(char *str,char c, int *i)
{
	while (str[*i] && str[*i] != c)
		(*i)++;
}

void	ft_quote(char *prompt, int *i, int start, t_command_line *line)
{
	while (prompt[i] &&)
	{
		/* code */
	}
	
	ft_next_char(prompt, prompt[*i], &i);
	ft_add_token(ft_substr(prompt, start, i), line);
}
t_command_line	*ft_loop_token(char *prompt)
{
	int				i;
	int				start;
	t_command_line	*line;

	line = ft_init_queue();
	if (!line)
		return (NULL);
	i = 0;
	while (prompt[i])
	{
		
		ft_skip_spaces(prompt, &i);
		start = i;
		if (prompt[i] == '\'' || prompt[i] == '"')
			ft_quote(prompt, &i, start, line);
		if (!is_redirect(&prompt[i]))
			i++;
		ft_add_token(ft_substr(prompt, start, i), line);
		i++;
	}
	return (line);
}

int	*ft_tokenization(char *prompt, t_shell *shell)
{
	t_command_line	*line;

	(void)shell;
	line = ft_loop_token(prompt);
	return (0);
}

void	ft_display(t_command_line *line)
{
	t_token	*current;

	current = line->first;
	while (current)
	{
		printf("content [%s] | token [%d]\n", current->content, current->type);
		current = current->next;
		if (current)
			printf(" | \n\\/");
	}
}

int	ft_parsing_prompt(char *prompt, t_shell *shell)
{
	t_command_line *line;
	if (ft_check_open_quote(prompt) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	line = ft_tokenization(prompt, shell);
	if (line == NULL)
		return (EXIT_FAILURE);
	ft_display(line);
	return (0);
}