/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:53:19 by fmontero          #+#    #+#             */
/*   Updated: 2024/07/23 17:07:49 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char		*get_line(char **acc);
static ssize_t	load_acc(char **acc, int fd);
static char		*last_line(char **acc);
static ssize_t	free_return(char *buffer, ssize_t bytes);

char	*get_next_line(int fd)
{
	static char		*acc[MAXFD];
	ssize_t			bytes;

	if (ft_strchr(acc[fd], '\n'))
		return (get_line(&acc[fd]));
	bytes = load_acc(&acc[fd], fd);
	if (bytes == -1)
	{
		free(acc[fd]);
		return (NULL);
	}
	if (bytes == 0)
		return (last_line(&acc[fd]));
	return (get_line(&acc[fd]));
}

static ssize_t	load_acc(char **acc, int fd)
{
	ssize_t	bytes;
	char	*tmp;
	char	*buffer;

	while (1)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (-1);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1 || bytes == 0)
			return (free_return(buffer, bytes));
		buffer[bytes] = 0;
		tmp = gnl_concat(*acc, buffer);
		if (!tmp)
			return (free_return(buffer, -1));
		free(*acc);
		*acc = tmp;
		if (ft_strchr(buffer, '\n'))
			return (free_return(buffer, bytes));
		free(buffer);
	}
}

static char	*get_line(char **acc)
{
	char	*line;
	char	*next_line;

	next_line = ft_strchr(*acc, '\n') + 1;
	line = ft_substr(*acc, 0, next_line - *acc);
	next_line = ft_strdup(next_line);
	free(*acc);
	if (line == NULL || next_line == NULL)
	{
		free(line);
		free(next_line);
		return (NULL);
	}
	*acc = next_line;
	return (line);
}

static char	*last_line(char **acc)
{
	char	*line;

	if (*acc)
	{
		line = ft_strdup(*acc);
		free(*acc);
		*acc = NULL;
		return (line);
	}
	return (NULL);
}

static ssize_t	free_return(char *buffer, ssize_t bytes)
{
	free(buffer);
	return (bytes);
}
