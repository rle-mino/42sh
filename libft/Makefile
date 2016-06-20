# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/10 18:07:20 by dsonetha          #+#    #+#              #
#    Updated: 2016/06/15 15:26:47 by rle-mino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =	ft_memccpy.c ft_putendl_fd.c ft_strdel.c \
		ft_strmapi.c ft_strsub.c ft_atoi.c	ft_memchr.c	ft_putnbr.c	ft_strdup.c \
		ft_strncat.c ft_strtrim.c ft_bzero.c ft_memcmp.c ft_putnbr_fd.c	\
		ft_strequ.c	ft_strncmp.c ft_tolower.c ft_isalnum.c ft_memcpy.c \
		ft_putstr.c	ft_striter.c ft_strncpy.c ft_toupper.c ft_isalpha.c \
		ft_memdel.c	ft_putstr_fd.c ft_striteri.c ft_strnequ.c ft_isascii.c\
		ft_memmove.c ft_strcat.c ft_strjoin.c ft_strnew.c ft_isdigit.c \
		ft_memset.c ft_strchr.c	ft_strlcat.c ft_strnstr.c ft_isprint.c \
		ft_putchar.c ft_strclr.c ft_strlcpy.c ft_strrchr.c ft_itoa.c \
		ft_putchar_fd.c	ft_strcmp.c	ft_strlen.c	ft_strsplit.c ft_memalloc.c \
		ft_putendl.c ft_strcpy.c ft_strmap.c ft_strstr.c ft_sjoinpath.c \
		get_next_line.c quit_error.c ft_abs.c ft_start_str.c ft_cmdsplit.c \
		ft_strlink.c ft_str_trunc.c quit_error_fd.c ft_strnlink.c no_char.c \
		ft_tabdel.c ft_xenostr.c ft_lstmap.c ft_lstiter.c ft_lstadd.c \
		ft_lstdel.c ft_lstdelone.c ft_lstnew.c ft_putptr.c ft_reverse.c \
		count_char.c ft_strndup.c ft_str_insert_char.c ft_str_del_char.c \
		check_bracket.c ft_strfill.c no_double_char.c ft_sdouble_trunc.c \
		ft_isspace.c ft_cmdsplit_dquote.c ft_cmdsplit_squote.c ft_cpy_tab.c\
		ft_char_to_string.c ft_backsplit.c ft_backslash_check.c \
		epur_backslash.c back_strchr.c ft_word_counter.c ft_bananasplit.c \

HEADER = libft.h

HEAD_PATH = ../includes/

OFILES = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -c

CC = gcc

.PHONY: clean

all: $(NAME)

$(NAME):
	@$(CC) $(FLAGS) -I $(HEAD_PATH) $(SRCS)
	@ar rcs $(NAME) $(OFILES)
	@echo "Libft created"

clean:
	@/bin/rm -f $(OFILES)
	@echo "Libft cleaned"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "Libft destroyed"

re: fclean all
