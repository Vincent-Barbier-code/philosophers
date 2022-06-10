# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/11 15:57:54 by vbarbier          #+#    #+#              #
#    Updated: 2021/12/13 06:53:52 by vbarbier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

FILES = ft_putchar_fd.c\
		ft_strlen.c\
		ft_putstr_fd.c\
		ft_itoa.c\
		ft_putnbr_fd.c\
		ft_putnbr_base.c\
		ft_putnbr_point.c\
		ft_printf.c\
		ft_putnbr_unsigned.c\


	OBJS= $(FILES:.c=.o)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: bonus all clean fclean re

