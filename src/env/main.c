/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:41:11 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/11/22 16:01:13 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gc.h"
#include "../../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void)av;
	if (ac != 1)
		return (1);
	shell = env_init(env);
	if (!shell)
		return (printf("Failed to initialize shell environement\n"), 1);
	if (fill_env_list(shell) != 0)
		return (printf("Failed to initialize the linked environement list\n"),
				1); //needed to be freed later
	print_list(shell);
	free_env_list(shell);
	free(shell);
	return (0);
}
/*
 
	-dans la version finale dnas le main definir le t_shell puis env init et enfin 
 fill_env_list
  -ajouter les free a voir si le garbage collector ffonctionne avec 
 
 */
// void	print_list(t_shell *list)
// {
// 	t_env	*current;
// 	size_t	i;

// 	if (!list || !list->head || !list->env)
// 	{
// 		printf("empty list\n");
// 		return ;
// 	}
// 	current = list->head;
// 	i = 0;
// 	while (current)
// 	{
// 		i++;
// 		printf("Node %zu:\n", i);
// 		printf("  key : %s\n", current->key);
// 		printf("  value : %s\n", current->value);
// 		printf("  Raw   : %s=%s\n", current->key, current->value);
// 		printf("-----------------\n");
// 		current = current->next;
// 	}
// 	printf("End of the list\n\n");
// }

void	print_list(t_shell *list)
{
	t_env	*current;

	if (!list || !list->head || !list->env)
	{
		printf("empty list\n");
		return ;
	}
	current = list->head;
	while (current)
	{
		printf("%s = %s\n", current->key, current->value);
		current = current->next;
	}
	printf("End of the list\n\n");
}
