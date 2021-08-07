/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishigak <tishigak@student.42toky...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 01:54:50 by tishigak          #+#    #+#             */
/*   Updated: 2021/08/01 22:45:50 by tishigak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	if (!(char)c)
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

static	char	*ft_gnl_substr(char *s, unsigned int start, size_t len)
{
	size_t	length;
	char	*ptr;
	size_t	i;

	length = ft_strlen(s);
	if (length <= start)
		length = 0;
	else
		length = length - start;
	if (length > len)
		length = len;
	ptr = malloc(length + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < length)
	{
		*(ptr + i) = *(s + start + i);
		i++;
	}
	*(ptr + length) = '\0';
	return (ptr);
}

int	ft_gnl_split(char **strage, char **line)
{
	char	*split_ptr;
	char	*tmp;

	split_ptr = ft_gnl_strchr(*strage, '\n');
	if (!split_ptr)
	{
		if (*strage)
			*line = ft_strdup(*strage);
		else
			*line = ft_strdup("");
		free(*strage);
		if (!*line)
			return (1);
		*strage = NULL;
	}
	else
	{
		*line = ft_gnl_substr(*strage, 0, split_ptr - *strage);
		tmp = *strage;
		*strage = ft_strdup(split_ptr + 1);
		free(tmp);
		if (!*line || !*strage)
			return (1);
	}
	return (0);
}
