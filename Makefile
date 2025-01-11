NAME = philo
HEADER = -I./include
CFLAGS = -Wall -Wextra -Werror
SRC = src/main.c

OBJ = $(SRC:src/%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $@

obj/%.o: src/%.c
	mkdir -p obj
	cc $(HEADER) -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all