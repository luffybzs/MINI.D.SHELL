/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:11:39 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/10/22 17:07:41 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_to_left_str(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr_spe(left_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		left_str = ft_strjoin_spe(left_str, buff);
	}
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (left_str)
		{
			free(left_str);
			left_str = NULL;
		}
		return (NULL);
	}
	left_str = ft_read_to_left_str(fd, left_str);
	if (!left_str)
		return (NULL);
	line = ft_get_line(left_str);
	left_str = ft_new_left_str(left_str);
	if (!line && left_str)
	{
		free(left_str);
		left_str = NULL;
	}
	return (line);
}

// int	main(void)
// {
// 	char *line;
// 	// int		i;
// 	int fd1;
// 	// int		fd2;
// 	// int		fd3;
// 	fd1 = open("tests/test.txt", O_RDONLY);
// 	// fd2 = open("tests/test2.txt", O_RDONLY);
// 	// fd3 = open("tests/test3.txt", O_RDONLY);
// 	// i = 1;
// 	line = get_next_line(fd1);
// 		// printf("line : %s", line);

// 	while (line != NULL)
// 	{

// 		printf("line : %s", line);
// 		free(line);
// 		line = get_next_line(fd1);
// 		// line = get_next_line(fd2);
// 		// printf("line [%02d]: %s", i, line);
// 		// free(line);
// 		// line = get_next_line(fd3);
// 		// printf("line [%02d]: %s", i, line);
// 		// free(line);
// 		// i++;
// 	}
// 	free(line);
// 	close(fd1);
// 	// close(fd2);
// 	// close(fd3);
// 	return (0);
// }