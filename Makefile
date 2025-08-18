CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -pthread
NAME = philo
SRC = main.c $(wildcard ./**/*.c)
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
