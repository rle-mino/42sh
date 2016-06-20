# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/02 17:54:24 by jaubard           #+#    #+#              #
#    Updated: 2016/06/20 14:45:49 by ishafie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##COLORS

EOC = \033[1;37m
RED = \033[1;31m
GREEN = \033[1;32m

DEBUG = no

NAME		=				42sh

SRC_NAME	=				auto_complete.c					\
							auto_complete2.c				\
							auto_complete3.c				\
							auto_complete_display.c			\
							buffer_parse.c					\
							call_builtins.c					\
							ft_back_quote_tools_2.c			\
							clear_str.c						\
							display_line.c					\
							edit_line.c						\
							edit_line_pairing.c				\
							easy_list.c						\
							easy_list2.c					\
							exec_shrc.c						\
							env_err.c						\
							ft_args_env.c					\
							ft_back_quote.c					\
							ft_back_quote_tools.c			\
							ft_del_back.c					\
							ft_err.c						\
							ft_err_fd.c						\
							ft_get_env.c					\
							ft_go_home.c					\
							ft_llredir.c					\
							ft_logical_operator.c			\
							ft_other.c						\
							ft_other2.c						\
							ft_other3.c						\
							ft_other4.c						\
							ft_other5.c						\
							ft_other6.c						\
							ft_other7.c						\
							ft_other8.c						\
							ft_other9.c						\
							ft_export_temp.c				\
							ft_pipe_tool.c					\
							ft_pipe.c						\
							ft_prompt.c						\
							ft_prompt_2.c					\
							ft_putint.c						\
							ft_redirect.c					\
							ft_sh1.c						\
							ft_signal.c						\
							ft_subshell.c					\
							ft_subshell_2.c					\
							ft_subshell_check.c				\
							ft_temp.c						\
							get.c							\
							get2.c							\
							get_clipboard.c					\
							glob.c							\
							glob_match.c					\
							glob_tools.c					\
							glob_tools2.c					\
							help_logical_operator.c			\
							history.c						\
							history2.c						\
							history3.c						\
							history4.c						\
							init_term.c						\
							leaks.c							\
							line.c							\
							move.c							\
							move2.c							\
							norme.c							\
							norme_err.c						\
							norme_err2.c					\
							norme_export.c 					\
							norme_pipe.c					\
							norme_read.c					\
							norme_redir.c					\
							norme_redir2.c					\
							pairing.c						\
							pairing2.c						\
							prompt_git.c					\
							red_error.c						\
							seg_signal.c					\
							tabulation_tree.c				\
							tabulation_tree_action.c		\
							tabulation_tree_display.c		\
							to_is.c							\
							variable.c						\
							variable_tool.c					\
							read.c 							\
							read_flags.c 					\
							reset_and_clear.c				\
							r_redir_help.c					\
							r_detect_redir_out.c			\
							r_detect_redir_in.c				\
							r_redir.c						\
							r_redir_error.c					\
							r_redir_inout.c					\
							is_script.c						\
							is_script_2.c					\
							shell_script.c					\
							shell_script_2.c				\
							shell_script_cdt.c				\
							shell_script_if.c				\
							shell_script_for.c				\
							shell_script_until.c			\
							shell_script_while.c			\
							sc_first_method_for.c			\
							sc_first_method_if.c			\
							sc_first_method_if_2.c			\
							sc_first_method_if_3.c			\
							sc_tools_for.c					\
							sc_check_for.c					\
							sc_check_until.c				\
							sc_check_while.c				\
							sc_check_if.c					\
							sc_check_if_two.c				\
							sc_check_if_three.c				\
							sc_check_if_four.c				\
							ft_builtin_reset.c				\
							ft_builtin_clear.c				\

OBJ_NAME	=		$(SRC_NAME:.c=.o)
OBJ_PATH	=		obj/
SRC_PATH	=		src/
OBJ			=		$(addprefix $(OBJ_PATH), $(OBJ_NAME))
SRC			=		$(addprefix $(SRC_PATH), $(SRC_NAME))

##DEBUG MODE
ifneq ($(DEBUG), no)
	FLAGS		=		-Wall -Wextra -Werror -g
else
	FLAGS		=		-Wall -Wextra -Werror
endif

.PHONY: all, clean, fclean, re

$(NAME): $(OBJ)
	make -C libft
	gcc -o $(NAME) $(FLAGS) -lcurses $(OBJ) -lft -L ./libft -I includes

all: $(NAME)

ifeq ($(DEBUG), yes)
	@echo "${RED}Generated in DEBUG mode${EOC}"
else
	@echo "${GREEN}Generated in RELEASE mode ${EOC}"
endif

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p obj
	gcc $(FLAGS) -c $< -o $@ -I includes

clean:
	make -C libft/ fclean
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all
