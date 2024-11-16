/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:46:59 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/16 15:57:26 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/* Définition des couleurs pour le prompt */
# define RED "\001\033[1;31m\002"
# define GREEN "\001\033[1;32m\002"
# define YELLOW "\001\033[1;33m\002"
# define BLUE "\001\033[1;34m\002"
# define PURPLE "\001\033[1;35m\002"
# define CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[0m\002"

# define PIPE 5
# define WORD 0
# define SFX 1
# define L_RED 4
# define R_RED 6
# define RR_RED 8
# define FILE 10
# define LL_RED 13
# define END_OF_FILE 14

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct s_command_line
{
	t_token			*first;
}					t_command_line;

typedef struct s_shell
{
	char			**env;
}					t_shell;

//-------------------------------------//

int					ft_parsing_prompt(char *prompt, t_shell *shell);
int					ft_check_open_quote(char *prompt);

t_command_line		*ft_init_queue(void);
int					is_redirect(char *content);
void				ft_add_token(char *content, t_command_line *command);
int					ft_compute_token(t_token *before, char *new);
int					ft_parsing_prompt(char *prompt, t_shell *shell);
void				ft_add_cmd(char *command, t_command_line *line, int *i);
void				ft_add_redirect(char *command, t_command_line *line,
						int *i);
void				ft_skip_spaces(char *str, int *i);
int					ft_next_char(char *str, char c, int *i, int *j);
int					ft_len_word(char *command, int i, char c);
char				*ft_supp_quote(char *command, int i, int *j, char c);
int ft_check_list(t_command_line *line);
t_token	*ft_lstlast_mini(t_command_line *lst);
int ft_check_all_list(t_command_line *line);
int ft_isredirect(int token);
#endif