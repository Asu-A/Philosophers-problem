NAME = philo_two

GCC = gcc -Wall -Wextra -Werror

SRCS = philo_two.c philo_two_utils.c philo_two_helper.c utils.c time_functions.c

SROS = philo_two.o philo_two_utils.o philo_two_helper.o utils.o time_functions.o

INCLUSES = -I philo_two.h

all: $(NAME)

$(NAME): $(SROS)
	$(GCC) $(SRCS) -o $(NAME)

%.o : %.c philo_two.h
	$(GCC) -c $< -o $@ $(INCLUDES)

clean:
	rm -f $(SROS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, fclean, clean, re
