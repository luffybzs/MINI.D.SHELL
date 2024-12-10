/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:48:26 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/10 17:03:18 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_pwd(t_shell *shell)
{
	char *cwd;

	(void)shell;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		// g_signal_status = 1;
		shell->exit_status = 1;
		perror("pwd");
		return (1);
	}
	if (ft_print_pwd(cwd, 1) == EXIT_FAILURE)
		return (shell->exit_status= 1,/*g_signal_status = 1*/1);
	ft_free(cwd);
	// g_signal_status = 0;
	shell->exit_status = 0;
	return (0);
}

int	ft_print_pwd(char *s, int fd)
{
	size_t	check;

	check = 0;
	check = write(fd, s, ft_strlen(s));
	check += write(fd,"\n",1);
	if (check != (ft_strlen(s)+1))
		return (ft_putstr_fd("pwd: write error: No space left on device\n", 2),
				EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
