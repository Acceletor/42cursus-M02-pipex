NAME = pipex

#Directory
INC = -I ./include/
OBJ_DIR = obj/
LIBFT = ./libft/libft.a

#Compiler and Cflag
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = src/pipex.c src/pipex_utils.c

OBJ = $(SRCS:%.c=$(OBJ_DIR)%.o)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJ)
	@make -C ./libft
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) -o $(NAME)

all: $(NAME)
	@echo "\033[32m[Program is ready for use]\033[0m"

clean:
	$(RM) -r $(OBJ_DIR)
	@make clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	@make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re