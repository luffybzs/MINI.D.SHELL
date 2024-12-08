/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:34:03 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/08 08:05:42 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t	g_signal_status = 100;

// Fonction pour calculer la puissance
double power(double x, int n) {
    double result = 1.0;
    for (int i = 0; i < n; i++) {
        result *= x;
    }
    return result;
}

// Fonction pour calculer la factorielle
unsigned long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    unsigned long fact = 1;
    for (int i = 2; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

// Fonction pour approximer sin(x) avec la série de Taylor
double my_sin(double x) 
{
	double res;
	res = 0.0;
	for(int i = 0; i <= 10; i++){
		int sign = (i % 2 == 0) ? 1 : -1; // Alterne les signes
		res += sign * (power(x , 2 * i + 1) / factorial(2 * i + 1));
	}
	return(res);
}

double my_sin_scaled(double x) {
    // Applique un facteur d'échelle pour étendre la plage [-1, 1] à [0, 255]
    return (my_sin(x) + 1) * 127.5;  // Transforme [-1, 1] en [0, 255]
}
char *ft_print_color(int i)
{
	static char str[10000];
	int r;
	int b;
	int g;

	r = 128 + (int)(127 * my_sin(0.1 * i + 0)) % 256;   // Rouge
    g = 128 + (int)(127 * my_sin(0.1 * i + 2)) % 256;   // Vert
    b = 128 + (int)(127 * my_sin(0.1 * i + 4)) % 256;   // Bleu
	ft_s_printf(str,"\033[38;2;%d;%d;%dm%s\033[0m", r, g, b, "Mini.D.Shell -> ");
	return (str);
}


int	ft_loop_shell(char *prompt, t_shell *shell)
{
	int i;
	i = 0;
	while (1)
	{
		i = i % 128;
		ft_signal();
		prompt = readline(ft_print_color(i));		
		if (g_signal_status != 100)
		{
			g_signal_status = 100;
			continue ;
		}
		if (!prompt)
			break ;
		if (*prompt)
			add_history(prompt);
		if (ft_parsing_prompt(prompt, shell) == EXIT_FAILURE)
			shell->exit_status = 2;
		i += 10;
	}
	return (EXIT_FAILURE);
}
void	ft_fill_data(t_shell *shell, char **av)
{
	shell->shell_pid = getpid();
	shell->shell_name = ft_strdup(av[0]);
	shell->exit_status = 0;
	shell->previous_pipe_fd = -1;
}

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	t_shell	shell;

	(void)ac;
	/* signaux*/
	// setup_interactive_signals();
	prompt = NULL;
	memset(&shell, 0, sizeof(t_shell));
	shell.env = env;
	ft_fill_data(&shell, av);
	if (fill_env_list(&shell) != 0)
		return (printf("Failed to initialize the linked environement list\n"),
				1); // needed to be freed later + retour d erreur
	if (ft_loop_shell(prompt, &shell) == EXIT_FAILURE)
		return (ft_free(DESTROY), EXIT_FAILURE);
	return (ft_free(DESTROY), 0);
}

// int main(void)
// {
// 	struct sigaction sa;
// 	(void)sa;
// 	printf("size of sigaction : %lu\n", sizeof(struct sigaction));
// 	return (0);
// }
