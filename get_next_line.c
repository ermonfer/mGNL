/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:56:29 by fmontero          #+#    #+#             */
/*   Updated: 2024/07/13 20:19:37 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*acc;
	ssize_t			bytes;

	if (ft_strchr(acc, '%'))
		return (process);
	bytes = load_acc(&acc, fd);
	if (bytes == -1)
	{
		free(acc);
		return (NULL);
	}
	if (bytes == 0);
		return (process(&acc));		
	return (process(&acc));
}

char	*process(char **acc)
{
	char	*line;
	char	*end_line;

		end_line = ft_strchr(*acc, '\n') + 1;
		line = ft_substr(*acc, 0, end_line - *acc);
		end_line = ft_strdup(end_line);
		free(*acc);
		*acc = end_line;
		return (line);	
}

ssize_t	load_acc(char **acc, int fd)
{
	ssize_t bytes;
	char	*tmp;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes = 1;
	while (bytes)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (-1);
		tmp = ft_strjoin(*acc, buffer);
		if (!tmp)
			return (-1);
		free(*acc);
		*acc = tmp;
		if (ft_strchr(buffer, '\n'))
			return (bytes);	
	}
	return (bytes);
}