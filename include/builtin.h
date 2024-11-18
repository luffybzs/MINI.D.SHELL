/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:55:51 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/18 16:02:02 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "minishell.h"


// general function

int	ft_execute_command(t_shell *shell);
int	is_builtin(char *cmd);
int execute_builtin(t_token *cmd, t_shell *shell);

// builtin

int	ft_echo(t_token *cmd, t_shell *shell);

#endif