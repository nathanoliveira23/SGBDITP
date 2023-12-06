NAME = SGBDITP

CC = gcc
CLANG = clang

C_FLAGS = -std=c99 -Wall -Werror -Wextra -Wunnused -pedantic -lm

C_SOURCES = $(PWD)/src/*.c $(PWD)/utils/*.c

INCLUDE_PATH = -I/$(PWD)/includes

all: $(NAME)

$(NAME):
	$(CC) $(C_SOURCES) $(INCLUDE_PATH) -o $(NAME)
	./$(NAME)
