#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tishigak <tishigak@student.42toky...>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/11 03:09:50 by tishigak          #+#    #+#              #
#    Updated: 2021/08/02 01:02:53 by tishigak         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= pipex
CC		= gcc
CFLAGS		= -Wall -Werror -Wextra
SRCS		= get_next_line.c get_next_line_utils.c pipex.c pipex_utils.c libft/libft.a
SRCSB		= get_next_line.c get_next_line_utils.c pipex.c pipex_utils.c libft/libft.a
HEADERPATH	= -I ./

OBJS	= $(SRCS:.c=.o)
OBJSB	= $(SRCSB:.c=.o)

ifdef WITH_BONUS
ALL_OBJS = $(OBJS) $(OBJSB)
else
ALL_OBJS = $(OBJS)
endif

all:	libft $(NAME)

clean:
	rm -f $(OBJS)
	rm -f $(OBJSB)
	@make -C libft clean

%.o:	%.c libft.h
	$(CC) -c $(CFLAGS) -o $@ $<

fclean:	clean
	rm -f $(NAME)
	@make -C libft fclean

re:	fclean all

libft:
	@make -C libft
	@cp libft/libft.a .

bonus:
	@$(MAKE) WITH_BONUS=1 $(NAME)

$(NAME): $(ALL_OBJS) libft
	$(CC) -o $(NAME) $(ALL_OBJS) libft.a

.PHONY:	all clean fclean re bonus libft
