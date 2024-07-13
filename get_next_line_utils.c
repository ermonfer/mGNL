/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontero <fmontero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:57:11 by fmontero          #+#    #+#             */
/*   Updated: 2024/07/14 00:07:14 by fmontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	const unsigned char		*us;
	unsigned char			uc;

	us = (const unsigned char *)s;
	uc = (unsigned char)c;
	while (*us != uc)
	{
		if (*us++ == '\0')
			return (NULL);
	}
	return ((char *)us);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*copy;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s) + 1;
	copy = malloc(len);
	if (copy == NULL)
		return (NULL);
	while (len--)
		*copy++ = *s++;
	return (copy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	length;

	if (s == NULL)
		return (NULL);
	length = ft_strlen(s);
	if (start >= length)
		return (ft_strdup(""));
	if (length < len + start)
		len = length - start;
	subs = (char *)malloc(len + 1);
	if (subs == NULL)
		return (NULL);
	s += start;
	length = 0;
	while (len-- > 0)
		subs[length++] = *s++;
	subs[length] = '\0';
	return (subs);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	lens1;
	size_t	lens2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	res = malloc(lens1 + lens2 + 1);
	if (res == NULL)
		return (NULL);
	while (lens1--)
		*res++;
	while (lens2--)
		*res++;
	*res = '\0';
	return (res);
}
