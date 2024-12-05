/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:02:29 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/05 04:24:51 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_export(t_exec *current, t_shell *shell)
{
	t_env	*existing;
	int		i;
	int		status;

	i = 1;
	status = 0;
	current = shell->first_exec;
	if (!current->cmd[1])
		return (ft_export_without_arg(shell));
	while (current->cmd[i])
	{
		if (is_name_ok(current->cmd[i], shell))
			status = 1;
		else
		{
			existing = ft_find_env(shell, current->cmd[i]);
			if (!existing)
				add_new_env(current->cmd[i], shell);
			else if (ft_strchr(current->cmd[i], '='))
			{
				ft_free(existing->value);
				existing->value = get_value(current->cmd[i]);
			}
		}
		i++;
	}
	return (status);
}

int	is_name_ok(char *str, t_shell *shell)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (printf("%s: export '%s': not a valid identifier\n",
				shell->shell_name, str), 1); // gerer l erreur
	if ((str[0] != '_' && !ft_isalpha(str[i])))
		return (printf("%s: export '%s': not a valid identifier\n",
				shell->shell_name, str), 1); // gerer l erreur
	while (str[i] && str[i] != '=')
	{
		if ((str[i] != '_' && !ft_isalnum(str[i]) && str[i] != '='))
			return (printf("%s: export '%s': not a valid identifier\n",
					shell->shell_name, str), 1); // gerer l erreur
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

void	add_new_env(char *str, t_shell *shell)
{
	char	*new_key;
	char	*new_value;
	char	*equal_sign;
	t_env	*new;
	t_env	*current;

	if (!str || !shell)
		return ;
	current = shell->head;
	new = ft_malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = NULL;
	new->value = NULL;
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
	{
		new_key = ft_strdup(str);
		new_value = ft_strdup("");
		if (!new_key || !new_value)
		{
			ft_free_env_node(new);
			return ; // ft_free tout
		}
	}
	else
	{
		new_key = ft_substr(str, 0, equal_sign - str);
		if (*(equal_sign + 1) == '\0')
			new_value = ft_strdup("");
		else
			new_value = ft_strdup(equal_sign + 1);
		if (!new_key || !new_value)
			return ; // ft_free tout
	}
	if (!new_key || !new_value)
	{
		free_env_node(new);
		free_env_node(current);
		return ;
	}
	new->key = new_key;
	new->value = new_value;
	if (!shell->head)
		shell->head = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	new->next = NULL;
	return ;
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