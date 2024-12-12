/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:48:21 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/12 16:50:08 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static int	ft_handle_env_errors(t_exec *actual, t_shell *shell)
{
	if (!actual || !actual->cmd || !shell || !shell->head)
		return (EXIT_FAILURE);
	if (actual->cmd[1] && actual->cmd[1][0] == '-')
	{
		ft_putstr_fd("env: illegal option\n", 2);
		shell->exit_status = 125;
		return (EXIT_FAILURE);
	}
	if (actual->cmd[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		shell->exit_status = 125;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_env(t_exec *actual, t_shell *shell)
{
	t_env	*current;

	if (ft_handle_env_errors(actual, shell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	current = shell->head;
	while (current)
	{
		if (current->value[0] != 0)
			if (ft_print_env(current->key, "=", current->value,
					1) == EXIT_FAILURE)
				return (shell->exit_status = 1, 1);
		current = current->next;
	}
	shell->exit_status = 0;
	return (EXIT_SUCCESS);
}

int	ft_print_env(char *s1, char *s2, char *s3, int fd)
{
	size_t	check;

	check = 0;
	check = write(fd, s1, ft_strlen(s1));
	check += write(fd, s2, ft_strlen(s2));
	check += write(fd, s3, ft_strlen(s3));
	check += write(fd, "\n", 1);
	if (check != (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1))
		return (ft_putstr_fd("env: write error: No space left on device\n", 2),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
