ifndef VERBOSE
MAKEFLAGS += --silent
endif

NAME := philo

SRC := main.c cleanup.c data_init.c exec_utils.c  monitoring.c parse.c simulation.c

OBJ := $(SRC:.c=.o)

HEADER := philo.h

CC := cc

CFLAGS := -Wall -Werror -Wextra -pthread

RM := rm -f

RED := \033[1;30;41m

GREEN := \033[1;30;42m

OFF := \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I.
	@echo "$(GREEN) Executable Created $(OFF)"

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	@echo "$(RED) Executable Deleted $(OFF)"

re: fclean all

.PHONY: all clean fclean re