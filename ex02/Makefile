NAME := PmergeMe

SRC := 	PmergeMe.cpp \
		main.cpp

OBJ := $(SRC:.cpp=.o)

CC := c++

CFLAGS := -Wall -Wextra -Werror -std=c++98

GREEN := \033[0;32m

all: $(OBJ) $(NAME)

$(OBJ): %.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(GREEN) Compiling ex02 ... "
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN) Done! "

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.phony: all clean fclean re