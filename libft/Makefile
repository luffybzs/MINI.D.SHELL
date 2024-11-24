# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 20:49:13 by wdaoudi-          #+#    #+#              #
#    Updated: 2024/11/23 23:06:39 by ayarab           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

NAME = libft.a
OBJS_DIR = objs/
SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c \
	ft_memcmp.c ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c \
	ft_atoi.c ft_calloc.c ft_strdup.c ft_striteri.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_strlen_2d.c ft_strjoin_2d.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_isspace.c ft_strcmp.c ft_isseparator.c \
	get_next_line.c get_next_line_utils.c ft_strjoin_free.c

SRCSB = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
	ft_lstmap.c $(SRCS)

OBJS = $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
OBJSB = $(SRCSB:.c=.o)
OBJECTS_BONUS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJSB))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

VPATH = .:get_next_line

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS_PREFIXED)
	@ar rcs $(NAME) $(OBJECTS_PREFIXED) > /dev/null 2>&1
	@echo "$(GREEN)Libft Ready ✓$(RESET)"

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)Libft objects cleaned$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Libft fully cleaned$(RESET)"

re: fclean all

bonus: $(OBJECTS_BONUS_PREFIXED)
	@ar rcs $(NAME) $(OBJECTS_BONUS_PREFIXED) > /dev/null 2>&1
	@echo "$(GREEN)Libft Bonus Ready ✓$(RESET)"

.PHONY: all clean fclean re bonus