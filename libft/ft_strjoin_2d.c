/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:42:46 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/01 01:36:47 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strjoin_2d(char **tab, char *str)
{
	char	**res;
	int		i;
	int		len;

	if (!tab || !str)
		return (NULL);
	len = 0;
	while (tab[len])
		len++;
	res = ft_malloc(sizeof(char *) * (len + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = ft_strdup(tab[i]);
		if (!res[i])
		{
			while (--i >= 0)
				ft_free(res[i]);
			ft_free(res);
			return (NULL);
		}
		i++;
	}
	res[len] = ft_strdup(str);
	if (!res[len])
	{
		while (--i >= 0)
			ft_free(res[i]);
		ft_free(res);
		return (NULL);
	}
	res[len + 1] = NULL;
	return (res);
}

 void	ft_free_2d(char **tab)
{
	int i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		ft_free(tab[i]);
		i++;
	}
	ft_free(tab);
}