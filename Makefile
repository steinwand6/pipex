#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tishigak <tishigak@student.42toky...>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/11 03:09:50 by tishigak          #+#    #+#              #
#    Updated: 2021/08/02 21:32:14 by tishigak         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= pipex
CC		= gcc
CFLAGS		= -Wall -Werror -Wextra
SRCS		= srcs/ft_putchar_fd.c srcs/ft_putendl_fd.c srcs/ft_putnbr_fd.c srcs/ft_putstr_fd.c srcs/ft_split.c srcs/ft_strdup.c \
			srcs/ft_strjoin.c srcs/ft_strlen.c srcs/ft_strncmp.c srcs/get_next_line.c srcs/get_next_line_utils.c \
			srcs/pipex.c srcs/pipex_utils.c
SRCSB		= srcs/ft_putchar_fd.c srcs/ft_putendl_fd.c srcs/ft_putnbr_fd.c srcs/ft_putstr_fd.c srcs/ft_split.c srcs/ft_strdup.c \
			srcs/ft_strjoin.c srcs/ft_strlen.c srcs/ft_strncmp.c srcs/get_next_line.c srcs/get_next_line_utils.c \
			srcs/pipex.c srcs/pipex_utils.c
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
	$(CC) -c $(CFLAGS) -o $@ $< $(HEADERPATH)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

bonus:
	@$(MAKE) WITH_BONUS=1 $(NAME)

$(NAME): $(ALL_OBJS)
	$(CC) -o $(NAME) $(ALL_OBJS) $(HEADERPATH)

.PHONY:	all clean fclean re bonus
