/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:51:46 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/06/05 13:23:00 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	i;
	size_t	j;

	j = 0;
	lendst = 0;
	lensrc = ft_strlen((const char *)src);
	while (lendst < size && dst[lendst] != '\0')
		lendst++;
	if (lendst == size)
		return (size + lensrc);
	i = lendst;
	while (src[j] != '\0' && i < size - 1)
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	return (lendst + lensrc);
}
