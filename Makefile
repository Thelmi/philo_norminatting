NAME = philo

SRC = program.c helpers.c input_parsing.c parsing.c philo_utilities.c routine_utilities.c

OBJ = $(SRC:.c=.o)

CFLAGS = cc -Wall -Wextra -Werror
# lpthread
all: $(NAME)

$(NAME): $(OBJ)
	$(CFLAGS) $(OBJ) -o $(NAME) -lpthread

%.o:%.c
	$(CFLAGS) -c $< -o $@

re: fclean all

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

.PHONY: all re clean fclean 
