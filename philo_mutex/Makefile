NAME = philo_one

GCC = gcc -Wall -Wextra -Werror

SRCS = philo_one.c philo_one_utils.c philo_one_helper.c utils.c time_functions.c

SROS = philo_one.o philo_one_utils.o philo_one_helper.o utils.o time_functions.o

INCLUSES = -I philo_one.h

all: $(NAME)

$(NAME): $(SROS)
	$(GCC) $(SRCS) -o $(NAME)

%.o : %.c philo_one.h
	$(GCC) -c $< -o $@ $(INCLUDES)

clean:
	rm -f $(SROS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, fclean, clean, re
