/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:55:51 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/12 17:41:23 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

// general function

int		ft_execute_command(t_exec *current, t_shell *shell);
int		is_builtin(char *cmd);
void	execute_builtin(t_exec *cmd, t_shell *shell);

// builtin

int		ft_echo(t_exec *cmd, t_shell *shell);
void	handle_double_quote(t_shell *shell, int is_n, char *current, int i);
int		ft_env(t_exec *actual, t_shell *shell);
int		ft_print_env(char *s1, char *s2, char *s3, int fd);
int		ft_pwd(t_shell *shell);
int		ft_print_pwd(char *s, int fd);

/* cd */
int		ft_cd(t_exec *current, t_shell *shell);
int		execute_cd(char *path, char *old_pwd, t_shell *shell);
int		handle_cd_args(t_exec *current, t_shell *shell);
int		handle_cd_no_args(t_shell *shell, char **path);
void	handle_cd_error(char *path, t_shell *shell);
int		update_pwd_env(t_shell *shell, char *old_pwd);
t_env	*update_or_create_env(t_env *head, char *key, char *value);
char	*get_env_for_cd(t_env *head, char *key);

/* export */

int		ft_export(t_exec *current, t_shell *shell);
int		is_name_ok(char *str, t_shell *shell);
int		is_already_in_list(char *looking_for, t_shell *shell);
char	*get_value(char *str);
void	add_new_env(char *str, t_shell *shell);
int		ft_export_without_arg(t_shell *shell);
t_env	*ft_find_env(t_shell *shell, char *key);
void	*ft_free_env_node(t_env *node);
int		handle_export_arg(char *arg, t_shell *shell);
void	print_identifier_error(char *str, t_shell *shell);
int		check_empty_name(char *str, t_shell *shell);
int		check_first_char(char *str, t_shell *shell);
t_env	*init_env_node(void);
int		set_key_value(t_env *new, char *str, char *equal_sign);
// void	add_to_env_list(t_shell *shell, t_env *new);

/* unset */

int		ft_unset(t_exec *current, t_shell *shell);
int		is_name_ok_unset(char *str, t_shell *shell);
void	looking_and_sup(char *str, t_shell *shell);

/* exit */

int		ft_exit(t_exec *current, t_shell *shell);
int		handle_overflow(long res, char digit);
long	ft_atoi_spe(char *str);
void	ft_end_exit(t_shell *shell, int status, t_exec *current);
int		check_numeric_arg(char *arg);
// void	ft_end_exit(t_shell *shell, int status, t_exec *current);
int		handle_no_args(t_exec *current, t_shell *shell);
int		handle_numeric_error(t_exec *current, t_shell *shell);

/* signal */

// int ft_setup_signal_handler(t_shell_mode mode);
t_shell	*get_shell_instance(void);
void	set_shell_instance(t_shell *shell);

#endif