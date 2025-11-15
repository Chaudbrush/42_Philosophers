ifndef VERBOSE
MAKEFLAGS += --silent
endif

NAME := philo_bonus

SRC := main_bonus.c data_init_bonus.c exec_utils_bonus.c exit_bonus.c \
		monitor_bonus.c parent_utils_bonus.c parse_bonus.c simulation_bonus.c 

OBJ := $(SRC:.c=.o)

HEADER := philo_bonus.h

CC := cc

CFLAGS := -Wall -Werror -Wextra

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