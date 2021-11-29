NAME = container
CC = clang++
CFLAGS = -Wall -Werror -Wextra -std=c++11 -g3 -fsanitize=address
SRC = main.cpp

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re