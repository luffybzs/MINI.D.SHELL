# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 02:37:51 by ayarab            #+#    #+#              #
#    Updated: 2024/12/12 17:43:51 by wdaoudi-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

GARBAGE = $(addprefix garbage_collector/, gc.c gc_utils.c );

SRCS = $(addprefix src/, main.c tokenization/ft_start_parsing.c tokenization/ft_queue_functions.c tokenization/ft_parsing_utils.c \
tokenization/ft_add_cmd.c tokenization/ft_check_list.c tokenization/ft_parsing_utils2.c tokenization/ft_error_parsing.c \
builtin/gen.c builtin/echo.c builtin/env.c builtin/pwd.c env/env_list.c expand/ft_expand.c tokenization/ft_struc_for_exec.c tokenization/ft_start_cmd.c \
builtin/cd.c builtin/export.c builtin/unset.c exec/ft_access_cmd.c exec/ft_find_the_path.c tokenization/ft_fonction_parsing.c exec/ft_heredoc.c garbage_collector/gc_utils.c garbage_collector/gc.c \
builtin/exit.c  signal/signals.c exec/ft_open_file.c exec/ft_fonction_exec.c ft_s_printf/ft_s_base_printf.c ft_s_printf/ft_s_printf.c ft_s_printf/ft_s_printf_str.c exec/ft_heredoc2.c \
exec/ft_heredoc3.c exec/ft_access_cmd2.c garbage_collector/gc_utils2.c expand/ft_expand2.c \
env/env_list2.c builtin/export2.c builtin/export3.c builtin/exit2.c builtin/cd2.c )

INCLUDES = ./includes

LIB_DIR = ./libft
LIBFT = $(LIB_DIR)/libft.a
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g3 

NAME = minishell

all : $(LIBFT) $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -c  $< -o $@ 

$(LIBFT):
	make -C ./libft

$(NAME):  $(OBJS)
	$(CC) $(CFLAGS) -I $(INCLUDES)  $(OBJS) -o $(NAME) $(LIBFT) -lreadline 

clean:
	rm -f $(OBJS)
	make clean -C ./libft 

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re