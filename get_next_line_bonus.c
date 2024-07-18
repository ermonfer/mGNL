/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:56:29 by fmontero          #+#    #+#             */
/*   Updated: 2024/07/18 18:52:32 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

static char		*get_line(char **acc);
static ssize_t	load_acc(char **acc, int fd);
static t_fd_acc *get_fd_acc(t_fd_acc **head, int fd);
static void free_fd_acc(t_fd_acc **head, int fd);

/**
 * Reads the next line from the given file descriptor.
 * Manages multiple file descriptors using a linked list of accumulators.
 */ 
char	*get_next_line(int fd)
{
	static t_fd_acc	*head;
	t_fd_acc		*current_fd;
	ssize_t			bytes;
	char			*line;

	current_fd = get_fd_acc(&head, fd);
	if (ft_strchr(current_fd->acc, '\n'))
		return (get_line(&current_fd->acc));
	bytes = load_acc(&current_fd->acc, fd);
	if (bytes == -1)
	{
		free_fd_acc(fd);
		return (NULL);
	}
	if (bytes == 0)
	{
		if (current_fd->acc)
		{
			line = ft_strdup(current_fd->acc);
			free_fd_acc(fd);
			acc = NULL;
			return (line);
		}
		return (NULL);
	}
	return (get_line(&acc));
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

/**
 * Retrieves the accumulator node for a given file descriptor.
 * If the node does not exist, it creates a new one and adds it to the list.
 */ 
static t_fd_acc *get_fd_acc(t_fd_acc **head, int fd)
{
    t_fd_acc *current;

	current = *head;
    while (current)
    {
        if (current->fd == fd)
            return current;
        current = current->next;
    }
    current = malloc(sizeof(t_fd_acc));
    if (current == NULL)
        return NULL;
    current->fd = fd;
    current->acc = NULL;
    current->next = *head;
    *head = current;
    return current;
}

/**
 * Frees the accumulator node for a given file descriptor.
 */
 static void free_fd_acc(t_fd_acc **head, int fd)
{
    t_fd_acc *current;
    t_fd_acc *prev;

	current = *head;
	prev = NULL;
    while (current)
    {
        if (current->fd == fd)
        {
            if (prev)
                prev->next = current->next;
            else
                *head = current->next;
            free(current->acc);
            free(current);
            return ;
        }
        prev = current;
        current = current->next;
    }
}
