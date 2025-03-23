CC=gcc
CFLAGS=-Wall -Wextra -g

gameoflife: PROIECT-GAMEOFLIFE.c
	$(CC) $(CFLAGS) PROIECT-GAMEOFLIFE.c -o gameoflife

clean:
	rm -f gameoflife
