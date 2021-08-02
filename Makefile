#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tishigak <tishigak@student.42toky...>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/11 03:09:50 by tishigak          #+#    #+#              #
#    Updated: 2021/08/02 20:32:01 by tishigak         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= pipex
CC		= gcc
CFLAGS		= -Wall -Werror -Wextra
SRCS		= ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strdup.c ft_strjoin.c ft_strncmp.c get_next_line.c \
		get_next_line_utils.c pipex.c pipex_utils.c ft_strlen.c
SRCSB		= get_next_line.c get_next_line_utils.c pipex.c pipex_utils.c libft/libft.a
HEADERPATH	= -I ./

OBJS	= $(SRCS:.c=.o)
OBJSB	= $(SRCSB:.c=.o)

ifdef WITH_BONUS
ALL_OBJS = $(OBJS) $(OBJSB)
else
ALL_OBJS = $(OBJS)
endif

all:	$(NAME)

clean:
	rm -f $(OBJS)
	rm -f $(OBJSB)

%.o:	%.c
	$(CC) -c $(CFLAGS) -o $@ $<

fclean:	clean
	rm -f $(NAME)

re:	fclean all

bonus:
	@$(MAKE) WITH_BONUS=1 $(NAME)

$(NAME): $(ALL_OBJS)
	$(CC) -o $(NAME) $(ALL_OBJS)

.PHONY:	all clean fclean re bonus
