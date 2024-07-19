/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:53:19 by fmontero          #+#    #+#             */
/*   Updated: 2024/07/19 15:42:11 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char		*get_line(char **acc);
static ssize_t	load_acc(char **acc, int fd);

char	*get_next_line(int fd)
{
	static char		*acc[MAXFD];
	ssize_t			bytes;
	char			*line;

	if (ft_strchr(acc[fd], '\n'))
	return (get_line(&acc[fd]));
	bytes = load_acc(&acc[fd], fd);
	if (bytes == -1)
	{
		free(acc[fd]);
		return (NULL);
	}
	if (bytes == 0)
	{
		if (acc[fd])
		{
			line = ft_strdup(acc[fd]);
			free(acc[fd]);
			acc[fd] = NULL;
			return (line);
		}
		return (NULL);
	}
	return (get_line(&acc[fd]));
}

static char	*get_line(char **acc)
{
	char	*line;
	char	*next_line;

	next_line = ft_strchr(*acc, '\n') + 1;
	if (next_line == NULL)
	{
		free(*acc);
		return (NULL);
	}
	line = ft_substr(*acc, 0, next_line - *acc);
	next_line = ft_strdup(next_line);
	free(*acc);
	*acc = next_line;
	return (line);
}

static ssize_t	load_acc(char **acc, int fd)
{
	ssize_t	bytes;
	char	*tmp;
	char	buffer[BUFFER_SIZE + 1];

	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1 || bytes == 0)
			return (bytes);
		buffer[bytes] = 0;
		tmp = gnl_concat(*acc, buffer);
		if (!tmp)
			return (-1);
		free(*acc);
		*acc = tmp;
		if (ft_strchr(buffer, '\n'))
			return (bytes);
	}
}
