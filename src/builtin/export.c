/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:02:29 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/06 14:42:07 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static int	handle_export_arg(char *arg, t_shell *shell)
{
    t_env	*existing;

    if (is_name_ok(arg, shell))
        return (1);
    existing = ft_find_env(shell, arg);
    if (!existing)
        add_new_env(arg, shell);
    else if (ft_strchr(arg, '='))
    {
        ft_free(existing->value);
        existing->value = get_value(arg);
    }
    return (0);
}

int	ft_export(t_exec *current, t_shell *shell)
{
    int		i;
    int		status;

    i = 1;
    status = 0;
    if (!current->cmd[1])
    {
        ft_export_without_arg(shell);
        shell->exit_status = 0;
        return (0);
    }
    while (current->cmd[i])
    {
        if (handle_export_arg(current->cmd[i], shell))
            status = 1;
        i++;
    }
    shell->exit_status = status;
    return (status);
}


static void	print_identifier_error(char *str, t_shell *shell)
{
    ft_putstr_fd(shell->shell_name, 2);
    ft_putstr_fd(": export: `", 2);
    if (str)
        ft_putstr_fd(str, 2);
    ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	check_empty_name(char *str, t_shell *shell)
{
    if (!str || str[0] == '\0')
    {
        print_identifier_error(str, shell);
        return (1);
    }
    return (0);
}

static int	check_first_char(char *str, t_shell *shell)
{
    if (str[0] != '_' && !ft_isalpha(str[0]))
    {
        print_identifier_error(str, shell);
        return (1);
    }
    return (0);
}

int	is_name_ok(char *str, t_shell *shell)
{
    int	i;

    i = 0;
    if (check_empty_name(str, shell))
        return (1);
    if (check_first_char(str, shell))
        return (1);
    while (str[i] && str[i] != '=')
    {
        if (str[i] != '_' && !ft_isalnum(str[i]))
        {
            print_identifier_error(str, shell);
            return (1);
        }
        i++;
    }
    return (0);
}

t_env	*ft_find_env(t_shell *shell, char *key)
{
	t_env	*current;
	size_t	key_len;
	char	*equal_sign;

	if (!key || !shell || !shell->head)
		return (NULL);
	equal_sign = ft_strchr(key, '=');
	if (equal_sign)
		key_len = (size_t)(equal_sign - key);
	else
		key_len = ft_strlen(key);
	current = shell->head;
	while (current)
	{
		if (ft_strlen(current->key) == key_len && !ft_strncmp(key, current->key,
				key_len))
			return (current);
		current = current->next;
	}
	return (NULL);
}

char	*get_value(char *str)
{
	char	*part;

	part = ft_strchr(str, '=');
	if (!part)
		return (NULL);
	if (*(part + 1) == '\0')
		return (ft_strdup(""));
	return (ft_strdup(part + 1));
}

static t_env	*init_env_node(void)
{
    t_env	*new;

    new = ft_malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    new->key = NULL;
    new->value = NULL;
    new->next = NULL;
    return (new);
}

static int	set_key_value(t_env *new, char *str, char *equal_sign)
{
    char	*new_key;
    char	*new_value;

    if (!equal_sign)
    {
        new_key = ft_strdup(str);
        new_value = ft_strdup("");
    }
    else
    {
        new_key = ft_substr(str, 0, equal_sign - str);
        if (*(equal_sign + 1))
            new_value = ft_strdup(equal_sign + 1);
        else
            new_value = ft_strdup("");
    }
    if (!new_key || !new_value)
    {
        ft_free(new_key);
        ft_free(new_value);
        return (0);
    }
    new->key = new_key;
    new->value = new_value;
    return (1);
}

static void	add_to_env_list(t_shell *shell, t_env *new)
{
    t_env	*current;

    if (!shell->head)
        shell->head = new;
    else
    {
        current = shell->head;
        while (current->next)
            current = current->next;
        current->next = new;
    }
}

void	add_new_env(char *str, t_shell *shell)
{
    t_env	*new;
    char	*equal_sign;

    if (!str || !shell)
        return ;
    new = init_env_node();
    if (!new)
        return ;
    equal_sign = ft_strchr(str, '=');
    if (!set_key_value(new, str, equal_sign))
    {
        ft_free_env_node(new);
        return ;
    }
    add_to_env_list(shell, new);
}

int	ft_export_without_arg(t_shell *shell)
{
	t_env	*current;

	current = shell->head;
	while (current)
	{
		if (current->value[0])
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("declare -x %s\n", current->key);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

void	*ft_free_env_node(t_env *node)
{
	if (!node)
		return (NULL);
	if (node->key)
		ft_free(node->key);
	if (node->value)
		ft_free(node->value);
	ft_free(node);
	return (NULL);
}

/*



commande env: affiche toute la liste chainee qui possede une value
diffference avec export sans argument qui affihce toute la liste chainee sans distinction

if first caractere is not a _ or a letter error:
bash-5.1$ export  5test=abc
bash: export: `5test=abc': not a valid identifier

sensible a la casse :
bash-5.1$ export test = abc
bash: export: `=': not a valid identifier

bash: export: `=': not a valid identifier
bash-5.1$ export test =abc
bash: export: `=abc': not a valid identifier
bash-5.1$ export test= abc
bash-5.1$ env | grep test
test=

en cas d espace avant le egale errror et apres
le bash prends "test=''"


test des quotes:
test='abc' && test="abc" => test=abc
expand similaire aux autres expand

error:

export 1test    # "not a valid identifier"
export	A = 1    # "not a valid identifier"
export readonly # Si variable en lecture seule: "readonly variable"

*/