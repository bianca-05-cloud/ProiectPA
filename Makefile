all:
	gcc PROIECT-GAMEOFLIFE.c -o a -Wall -Wextra -g

run:
	./a input.txt output.txt
