#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tishigak <tishigak@student.42toky...>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/11 03:09:50 by tishigak          #+#    #+#              #
#    Updated: 2021/08/07 14:36:51 by tishigak         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= pipex
CC		= gcc
CFLAGS		= -Wall -Werror -Wextra
SHARE_SRC	= utils/ft_putchar_fd.c utils/ft_putendl_fd.c utils/ft_putnbr_fd.c \
		utils/ft_putstr_fd.c utils/ft_split.c utils/ft_strdup.c utils/ft_strjoin.c \
		utils/ft_strlen.c utils/ft_strncmp.c utils/pipex_utils.c utils/pipex_utils2.c
SRCS		= srcs/pipex.c
SRCSB		= bonus/get_next_line_bonus.c bonus/get_next_line_utils_bonus.c	bonus/pipex_bonus.c
HEADERPATH	= -I ./

OBJS		= $(SRCS:.c=.o)
OBJSB		= $(SRCSB:.c=.o)
SHARE_OBJS	= $(SHARE_SRC:.c=.o)

ifdef WITH_BONUS
ALL_OBJS = $(OBJSB) $(SHARE_OBJS)
else
ALL_OBJS = $(OBJS) $(SHARE_OBJS)
endif

all:	$(NAME)

clean:
	rm -f $(OBJS)
	rm -f $(OBJSB)
	rm -f $(SHARE_OBJS)

%.o:	%.c
	$(CC) -c $(CFLAGS) -o $@ $< $(HEADERPATH)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

bonus:
	@$(MAKE) WITH_BONUS=1 $(NAME)

debug: $(ALL_OBJS)
	$(CC) -o $(NAME) $(ALL_OBJS) $(HEADERPATH) -g -fsanitize=address

$(NAME): $(ALL_OBJS)
	$(CC) -o $(NAME) $(ALL_OBJS) $(HEADERPATH)

.PHONY:	all clean fclean re bonus debug