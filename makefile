CC = gcc
FLAGS = -Wall -Werror -std=gnu99
APP = sudoku

all: generate solve

generate: generate.c
	$(CC) $(FLAGS) $^ -o generate

solve: solve.c
	$(CC) $(FLAGS) $^ -o solve

clean:
	rm -rf generate solve
