# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/22 17:36:34 by lvincent          #+#    #+#              #
#    Updated: 2023/07/13 15:01:16 by lvincent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m

RED = \033[0;31m

RED_B = \033[1;31m

YELLOW = \033[1;33m

BLUE = \033[0;34m

RESET = \033[0m

NAME = philo

SRC = init.c main.c threads.c utils.c

OBJ = $(SRC:.c=.o)

CC = clang

CFLAGS = -Wall -Werror -Wextra -g

all : $(NAME)

.c.o :
	@echo "$(GREEN)Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME) : $(OBJ)
	@echo "$(BLUE)Compiled object files for $(NAME)$(RESET)"
	@$(CC) $(OBJ) $(LIBFT) $(CFLAGS) -lpthread	 -o $(NAME)
	@echo "$(YELLOW)Compiled $(NAME)$(RESET)"

clean :
	@rm -f $(OBJ)
	@echo "$(RED)Removed object files from project$(RESET)"

fclean :
	@rm -f $(OBJ)
	@echo "$(RED)Removed object files from project$(RESET)"
	@rm -f $(NAME)
	@echo "$(RED_B)Removed $(NAME)$(RESET)"

re : fclean all

.PHONY : all clean fclean re
