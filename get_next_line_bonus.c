/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helabiad <helabiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 16:55:58 by helabiad          #+#    #+#             */
/*   Updated: 2026/11/25 10:04:28 by helabiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_until_line(char *saved, int fd)
{
	char	*buffer;
	char	*tmp;
	ssize_t	read_bytes;

	buffer = malloc ((size_t)BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	buffer[0] = '\0';
	read_bytes = 1;
	while (!ft_strchr(buffer, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, (size_t)BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(saved), saved = NULL, free(buffer), NULL);
		buffer[read_bytes] = '\0';
		tmp = saved;
		saved = ft_strjoin(saved, buffer);
		free(tmp);
		if (saved == NULL)
			break ;
	}
	if (read_bytes == 0 && (saved == NULL || saved[0] == '\0'))
		return (free(saved), free(buffer), NULL);
	return (free(buffer), saved);
}

char	*ft_get_line(char **saved, int fd)
{
	char	*line;
	char	*tmp;
	size_t	i;
	size_t	j;

	tmp = read_until_line(*saved, fd);
	if (tmp == NULL)
		return (*saved = NULL, NULL);
	i = 0;
	while (tmp[i] != '\0' && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
		i++;
	line = malloc (i + 1);
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, tmp, i + 1);
	j = i;
	while (tmp[j] != '\0')
		j++;
	*saved = malloc (j + 1);
	if (*saved == NULL)
		return (free(tmp), free(line), NULL);
	ft_strlcpy(*saved, tmp + i, j + 1);
	return (free(tmp), line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*saved[FD_MAX];

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_get_line(&saved[fd], fd);
	if (line == NULL)
	{
		free(saved[fd]);
		saved[fd] = NULL;
		return (NULL);
	}
	return (line);
}
