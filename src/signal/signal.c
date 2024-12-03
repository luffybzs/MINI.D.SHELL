/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:41:50 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/03 16:03:45 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int ft_handle_signal(t_shell *shell)
{
    if (g_signal_status = INTERACTIVE_MODE)
    {
        handle_input_interactive(shell);
    }
    else
        handle_input(shell);
    return (0);
}

void handle_input_interactive(t_shell *shell)
{
    
}

void handle_input(t_shell *shell)
{
    
}