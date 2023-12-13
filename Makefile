NAME = SGBDITP

CC = gcc

C_FLAGS = -std=c99 -Wall -Werror -Wextra -Wunnused -pedantic -lm

C_SOURCES = $(PWD)/src/*.c $(PWD)/utils/*.c

INCLUDE_PATH = -I$(PWD)/includes

all: 
	$(CC) $(C_SOURCES) $(INCLUDE_PATH) -o $(NAME)
	./$(NAME)
