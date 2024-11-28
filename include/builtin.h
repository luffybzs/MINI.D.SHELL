/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:55:51 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/28 18:34:09 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

// general function

int		ft_execute_command(t_shell *shell);
int		is_builtin(char *cmd);
int		execute_builtin(t_token *cmd, t_shell *shell);

// builtin

int		ft_echo(t_token *cmd, t_shell *shell);
void	handle_double_quote(t_shell *shell, int is_n, char *current, int i);
int		ft_env(t_shell *shell);
int		ft_pwd(t_shell *shell);
int		ft_cd(t_shell *shell);

/* export */

int		ft_export(t_shell *shell);
int		is_name_ok(char *str, t_shell *shell);
int		is_already_in_list(char *looking_for, t_shell *shell);
char	*get_value(char *str);
void	add_new_env(char *str, t_shell *shell);
int		ft_export_without_arg(t_shell *shell);
t_env	*ft_find_env(t_shell *shell, char *key);
void	*ft_free_env_node(t_env *node);

/* unset */

int	ft_unset(t_shell *shell);
int	is_name_ok_unset(char *str, t_shell *shell);
void	looking_and_sup(char *str, t_shell *shell);

/* exit */

int	ft_exit(t_shell *shell);


#endif