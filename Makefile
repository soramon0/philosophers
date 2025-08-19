CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
NAME = philo
SRC = main.c ./src/philo.c ./src/misc.c ./src/parser.c ./src/state.c ./src/print.c ./src/sim.c ./src/atoi.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean leaks
