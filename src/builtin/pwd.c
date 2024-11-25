/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:48:26 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/24 15:58:57 by wdaoudi-         ###   ########.fr       */
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
		shell->exit_status = 1;
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	shell->exit_status = 0;
	return (0);
}