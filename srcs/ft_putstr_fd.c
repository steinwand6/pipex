/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishigak <tishigak@student.42toky...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 03:37:42 by tishigak          #+#    #+#             */
/*   Updated: 2021/08/02 20:15:02 by tishigak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	length;

	if (!s)
		return ;
	length = ft_strlen(s);
	while (length > INT_MAX)
	{
		write(fd, s, INT_MAX);
		length = length - INT_MAX;
		s = s + INT_MAX;
	}
	write(fd, s, length);
}
