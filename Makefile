# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 18:34:53 by ksuebtha          #+#    #+#              #
#    Updated: 2025/04/07 18:34:54 by ksuebtha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

#Directory
INC = -I ./include/
OBJ_DIR = obj/
LIBFT = ./libft/libft.a

#Compiler and Cflag
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = pipex.c pipex_utils.c

# Prepares a list of expected .o files
OBJ = $(SRCS:%.c=$(OBJ_DIR)%.o)

start: 
	@make all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Tells Make how to build those .o files
$(OBJ_DIR)%.o: src/%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
	@make -C ./libft
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) -o $(NAME)

all: $(NAME)
	@echo "\033[32m[Program is ready for use]\033[0m"

clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -C ./libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./libft

re: fclean all

.PHONY: start all clean fclean re