/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:55:51 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/05 04:45:07 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
#define BUILTIN_H

# include "minishell.h"

// general function

int	ft_execute_command(t_exec *current,
						t_shell *shell);
int		is_builtin(char *cmd);
void		execute_builtin(t_exec *cmd, t_shell *shell);

// builtin

int		ft_echo(t_exec *cmd, t_shell *shell);
void	handle_double_quote(t_shell *shell, int is_n, char *current, int i);
int		ft_env(t_exec *actual,t_shell *shell);
int		ft_pwd(t_shell *shell);
int		ft_cd(t_exec *current,t_shell *shell);

/* export */

int		ft_export(t_exec *current, t_shell *shell);
int		is_name_ok(char *str, t_shell *shell);
int	is_already_in_list(char *looking_for,
						t_shell *shell);
char	*get_value(char *str);
void	add_new_env(char *str, t_shell *shell);
int		ft_export_without_arg(t_shell *shell);
t_env	*ft_find_env(t_shell *shell, char *key);
void	*ft_free_env_node(t_env *node);

/* unset */

int		ft_unset(t_exec *current, t_shell *shell);
int		is_name_ok_unset(char *str, t_shell *shell);
void	looking_and_sup(char *str, t_shell *shell);

/* exit */

int		ft_exit(t_exec *current,t_shell *shell);

/* signal */

// int ft_setup_signal_handler(t_shell_mode mode);
t_shell	*get_shell_instance(void);
void	set_shell_instance(t_shell *shell);

#endif