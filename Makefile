CC = cc

GARBAGE = $(addprefix garbage_collector/, gc.c gc_utils.c );

SRCS = $(addprefix src/, main.c ft_start_parsing.c ft_queue_functions.c ft_parsing_utils.c ft_add_cmd.c ft_check_list.c ft_parsing_utils2.c)

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