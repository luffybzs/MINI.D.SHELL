/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:46:59 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/08 17:15:48 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "gc.h"
# include "ft_s_printf.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/signal.h>
# include <sys/stat.h>
# include <sys/types.h>
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

# define WORD 0
# define SFX 1
# define PIPE 5
# define L_RED 6
# define R_RED 7
# define RR_RED 11
# define LL_RED 10
# define FILE_TOKEN 20
# define END_OF_FILE 19
# define OUTFILE 22
# define INFILE 23
# define APPEND 24

extern volatile sig_atomic_t	g_signal_status;

typedef struct s_redir
{
	char *heredoc; // cpy le contenu du heredoc
	char *file;    // le nom du ficher a open et dup2
	int type;      // soit infile ou outfile
	struct s_redir				*next;
}								t_redir;

typedef struct s_redir_line
{
	t_redir						*head;
}								t_redir_line;

typedef struct s_exec
{
	char **cmd;     // le double tableau avc les suffix exemple "ls", "-la"
	t_redir *redir; // la liste de redir (pide, <, >, >> )
	int							pidt;
	struct s_exec				*next;
}								t_exec;

typedef struct s_exec_line
{
	t_exec						*first;
}								t_exec_line;

typedef struct s_token
{
	char						*content;
	int							type;
	struct s_token				*next;
}								t_token;

typedef struct s_command_line
{
	t_token						*first;
}								t_command_line;

typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef enum e_shell_mode
{
	INTERACTIVE,
	EXECUTING,
	HEREDOC,
}								t_shell_mode;

typedef struct s_signal_handler
{
	t_shell_mode				mode;
}								t_signal_handler;

typedef struct s_shell
{
	char						**env;
	char						**env_upt;
	char						**path;
	t_env						*head;
	t_command_line				*command;
	t_exec						*first_exec;
	int							previous_pipe_fd;
	// gerer les cas speciaux de l expand
	char *shell_name; // $0
	pid_t shell_pid;  //$$
	int exit_status;  // $?

	t_signal_handler			sig_handler;
}								t_shell;

typedef struct s_expand_state
{
	int							in_quote;
	char						*result;
	int							exit_status;
}								t_expand_state;

//-------------------------------------//
int ft_add_flag(t_exec *current);
char **ft_putflag(char **cmd);
int ft_cmp_flag(char *cmd);
int								ft_len_env(t_shell *shell);
char							**ft_lst_strdup(t_shell *shell);
int								ft_open_file(t_shell *shell, t_redir *current);
void	ft_open_heredoc(t_redir *current,
						t_shell *shell);
void	ft_open_outfile_append(char *file,
							t_shell *shell);
void							ft_open_outfile(char *file, t_shell *shell);
void							ft_open_infile(char *file, t_shell *shell);
int								ft_check_heredoc(t_shell *shell);
t_token	*ft_add_redir_exec(t_token *current,
							t_redir *file,
							t_exec *new_cmd);
int								ft_start_exec(t_shell *shell);
void	ft_lstadd_back_exec(t_exec **current,
							t_exec *newcmd);
void							ft_print_exec(t_shell *shell);
char							*ft_good_path(t_shell *shell, t_exec *current);
int								ft_test(t_shell *shell);
int								ft_get_env(t_shell *shell);
int								ft_parsing_prompt(char *prompt, t_shell *shell);
int								ft_check_open_quote(char *prompt);
int								ft_exec_loop(t_shell *shell);
t_command_line					*ft_init_queue(void);
int								is_redirect(char *content);
void	ft_add_token(char *content,
					t_command_line *command);
int								ft_compute_token(t_token *before, char *new);
int								ft_parsing_prompt(char *prompt, t_shell *shell);
void							ft_add_cmd(char *command, t_command_line *line,
									int *i);
void	ft_add_redirect(char *command,
						t_command_line *line,
						int *i);
int								ft_skip_spaces(char *str, int *i);
void							ft_next_char(char *str, char c, int *i, int *j);
int								ft_len_word(char *command, int i, char c);
int								ft_check_list(t_command_line *line);
t_token							*ft_lstlast_mini(t_command_line *lst);
int								ft_check_all_list(t_command_line *line);
int								ft_isredirect(int token);
void							ft_error_token(char *content);
void							ft_error_pide(char *content);
void							ft_error_double_redir(char *content);
void							ft_error_quote(void);
int								ft_is_file(int token);
int								ft_check_pide_and_redir(t_command_line *line);
void							ft_error_end_redir(void);
int								ft_struc_for_exec(t_shell *shell);
int								ft_start_cmd(t_token *current);
t_exec_line						*ft_init_queue_exec(void);
int								ft_nb_cmd(t_token *current);
// environnement management

t_shell							*env_init(char **env);
int								fill_env_list(t_shell *shell);
t_env							*create_env_node(char *env_str);
void							free_env_list(t_shell *shell);
void							free_env_node(t_env *node);
int								ft_findchar(const char *str, int c);
char							*ft_supp_quote2(char *command, char c, int i);
void							update_underscore_var(t_shell *shell,
									char *last_arg);
									
// expand

int								ft_expand(t_command_line *line, t_shell *shell);
int								ft_find_dollar(char *content, int *i);
char							*get_var_name(char *content);
int								get_var_len(char *str);
char							*get_var_value(char *var_name, t_shell *shell);
int	check_expand_state(char *str,
						t_expand_state *exp);
int								should_expand(t_expand_state *exp);

char							*expand_var(char *input, t_shell *shell,
									t_token *current);
int								handle_quotes(char c, t_expand_state *state);
void							handle_expansion(char *input, int *i,
									t_expand_state *state, t_shell *shell);
int								handle_special_var(char c, int *i,
									t_expand_state *state, t_shell *shell);
int								get_var_name_length(const char *str);
void							append_char(char **str, char c);
void							append_string(char **dst, const char *src);
char	*get_env_value(const char *name,
					t_shell *shell);

/* expand hd*/

char	*handle_expand_here_doc(char *str,
								t_shell *shell);
char	*handle_expand_here_doc(char *str,
								t_shell *shell);
void							append_char_spe(char *str, char c);

// test

void							print_list(t_shell *list);
int	ft_execute_command(t_exec *current,
						t_shell *shell);

/* signaux */

void							set_signal_child(void);
int								sig_event(void);
void							signal_handler(int sig);
void							ft_signal(void);

#endif