/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:42:46 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/24 02:35:54 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **ft_strjoin_2d(char **tab, char *str)
{
	char **res;
	int len;
	
	len = ft_strlen_2d(tab);

	res = malloc(sizeof(char **) * (len + 2));
	if (!res)
		return (NULL);
	res[len] = ft_strdup(str);
	res[len + 1] = NULL;
	return (res);
}