CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
NAME = philosophers
SRC = main.c $(shell find ./src -depth -maxdepth 1 -type f -name "*.c")
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

leaks:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

re: fclean all

.PHONY: clean leaks
