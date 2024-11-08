# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 17:03:30 by wdaoudi-          #+#    #+#              #
#    Updated: 2024/11/07 19:00:42 by wdaoudi-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
WHITE		= \033[97m
RED			= \033[91m
YELLOW		= \033[93m
GREY		= \033[90m
RESET		= \033[0m
GREEN		= \033[92m
CYAN		= \033[96m
BLUE		= \033[94m

# Program
NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# Directories
SRCS_DIR	= srcs/
INCLUDES_DIR = include/
OBJS_DIR	= objs/
LIBFT_DIR	= libft/

# Source files
SRCS_FILES	= main.c
SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS_FILES	= $(SRCS_FILES:.c=.o)
OBJS		= $(addprefix $(OBJS_DIR), $(OBJS_FILES))

# Libraries
LIBFT		= $(LIBFT_DIR)libft.a
READLINE_LIB = -lreadline

# Rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@if [ -f $(NAME) ]; then \
		echo "$(CYAN)minishell is up to date$(RESET)"; \
	else \
		printf "$(GREEN)▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰▰$(RESET)\n"; \
		echo "$(RED)   ▄████████    ▄█    █▄       ▄████████  ▄█        ▄█      $(RESET)"; \
		echo "$(RED)  ███    ███   ███    ███     ███    ███ ███       ███      $(RESET)"; \
		echo "$(RED)  ███    █▀    ███    ███     ███    █▀  ███       ███      $(RESET)"; \
		echo "$(RED)  ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄     ███       ███      $(RESET)"; \
		echo "$(RED)▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀     ███       ███      $(RESET)"; \
		echo "$(RED)         ███   ███    ███     ███    █▄  ███       ███      $(RESET)"; \
		echo "$(RED)   ▄█    ███   ███    ███     ███    ███ ███▌    ▄ ███▌    ▄$(RESET)"; \
		echo "$(RED) ▄████████▀    ███    █▀      ██████████ █████▄▄██ █████▄▄██$(RESET)"; \
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_LIB) -o $(NAME); \
		echo "$(GREEN)Minishell Ready ✓$(RESET)"; \
	fi

clean:
	@$(RM) $(OBJS)
	@rm -rf $(OBJS_DIR)
	@make -sC $(LIBFT_DIR) clean
	@echo "$(RED)Objects cleaned$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make -sC $(LIBFT_DIR) fclean
	@echo "$(RED)Everything cleaned$(RESET)"

re: fclean all

.PHONY: all clean fclean re