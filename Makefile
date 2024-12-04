CC = cc

GARBAGE = $(addprefix garbage_collector/, gc.c gc_utils.c );

SRCS = $(addprefix src/, main.c tokenization/ft_start_parsing.c tokenization/ft_queue_functions.c tokenization/ft_parsing_utils.c \
tokenization/ft_add_cmd.c tokenization/ft_check_list.c tokenization/ft_parsing_utils2.c tokenization/ft_error_parsing.c \
builtin/gen.c builtin/echo.c builtin/env.c builtin/pwd.c env/env_list.c expand/ft_expand.c tokenization/ft_struc_for_exec.c tokenization/ft_start_cmd.c \
builtin/cd.c builtin/export.c builtin/unset.c exec/ft_access_cmd.c exec/ft_find_the_path.c tokenization/ft_fonction_parsing.c exec/ft_heredoc.c garbage_collector/gc_utils.c garbage_collector/gc.c \
builtin/exit.c  signal/signals.c )

INCLUDES = ./includes

LIB_DIR = ./libft
LIBFT = $(LIB_DIR)/libft.a
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g3 -lncurses -ltinfo

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