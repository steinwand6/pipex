/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishigak <tishigak@student.42toky...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 01:49:28 by tishigak          #+#    #+#             */
/*   Updated: 2021/08/01 19:31:16 by tishigak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
#include "libft.h"

size_t	ft_strlen(const char *str);
int		get_next_line(int fd, char **line);
char	*ft_gnl_strchr(const char *s, int c);
int		ft_gnl_split(char **strage, char **line);

#endif
