/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishigak <tishigak@student.42toky...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 21:08:17 by tishigak          #+#    #+#             */
/*   Updated: 2021/08/06 23:35:27 by tishigak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_gnl_strjoin(char *s1, char *s2, size_t len2)
{
	size_t	len1;
	char	*ptr;
	size_t	i;

	if (!len2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	len1 = ft_strlen(s1);
	ptr = malloc(len1 + len2 + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	free(s1);
	while (*s2)
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	return (ptr);
}

ssize_t	ft_gnl_read_and_store(int fd, char **buf, char **strage)
{
	ssize_t		result;

	result = read(fd, *buf, 2000);
	if (result == -1)
	{
		free(*strage);
		free(*buf);
		return (-1);
	}
	(*buf)[result] = '\0';
	*strage = ft_gnl_strjoin(*strage, *buf, (size_t)result);
	return (result);
}

int	get_next_line(int fd, char **line)
{
	static char	*strage = NULL;
	char		*buf;
	ssize_t		result;

	if (fd < 0 || !line)
		return (-1);
	buf = (char *)malloc(2001);
	if (!buf)
		return (-1);
	result = 1;
	while (result != 0 && (strage == NULL || !ft_gnl_strchr(strage, '\n')))
	{
		result = ft_gnl_read_and_store(fd, &buf, &strage);
		if (result == -1)
			return (-1);
	}
	free(buf);
	if (ft_gnl_split(&strage, line))
		return (-1);
	return (strage != NULL);
}

int	ft_read_heredoc(t_pi *px_info, int fd)
{
	char	*line;
	int		result;
	int		length;

	result = 1;
	length = ft_strlen(px_info->limit);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		result = get_next_line(0, &line);
		if (result < 0)
			return (-1);
		if (!result
			|| ft_strncmp(line, px_info->limit, length + 1) == 0)
		{
			free(line);
			break ;
		}
		else
			ft_putendl_fd(line, fd);
	}
	if (close(fd) == -1)
		return (-1);
	return (0);
}
