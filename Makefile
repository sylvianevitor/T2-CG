all:
	@gcc *.c -o main -Wall -lm -lGL -lGLU -lglut -I.
	
run:
	@./main

debug:
	@gcc *.c -o main -O3 -Wall -lm -lGL -lGLU -lglut -I. -v -g -lm
	@valgrind --leak-check=full --show-leak-kinds=all -v ./main
