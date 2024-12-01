/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:11:39 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/01 01:36:47 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*ft_line(char *string)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!string[i])
		return (NULL);
	while (string[i] && string[i] != '\n')
		i++;
	tmp = ft_substr_spe(string, 0, i + 1);
	return (tmp);
}

char	*ft_save(char *string)
{
	int		i;
	char	*tmp;

	i = 0;
	while (string[i] && string[i] != '\n')
		i++;
	if (!string[i])
	{
		ft_free(string);
		return (NULL);
	}
	tmp = ft_substr_spe(string, i + 1, ft_strlen(string));
	ft_free(string);
	return (tmp);
}

char	*ft_read_fd(int fd, char *string)
{
	char	*buffer;
	int		res;

	buffer = ft_malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	res = 1;
	while (!ft_strchr(string, '\n') && res != 0)
	{
		res = read(fd, buffer, BUFFER_SIZE);
		if (res == -1)
			return (ft_free(buffer), ft_free(string), NULL);
		buffer[res] = '\0';
		string = ft_strjoin(string, buffer);
	}
	ft_free(buffer);
	return (string);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*string[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	string[fd] = ft_read_fd(fd, string[fd]);
	if (!string[fd])
		return (NULL);
	line = ft_line(string[fd]);
	string[fd] = ft_save(string[fd]);
	return (line);
}
