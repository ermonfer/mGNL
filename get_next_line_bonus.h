/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:32:45 by fmontero          #+#    #+#             */
/*   Updated: 2024/07/18 17:23:13 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*gnl_concat(const char *s1, const char *s2);

/**
 * Struct representing a file descriptor accumulator.
 * 
 * @fd: The file descriptor.
 * @acc: The accumulator string for the file descriptor.
 * @next: Pointer to the next node in the list.
 */
typedef struct s_fd_acc
{
    int fd;
    char *acc;
    struct s_fd_acc *next;
}	t_fd_acc;

#endif
