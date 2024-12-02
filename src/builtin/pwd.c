/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:48:26 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/02 17:29:41 by ayarab           ###   ########.fr       */
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
	ft_free(cwd);
	shell->exit_status = 0;
	return (0);
}