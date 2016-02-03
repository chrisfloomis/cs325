CFLAGS = -Wall -fpic -lm -std=c99 -w

all: main.c
	gcc -o program main.c $(CFLAGS)
	./program testing.txt
				
clean:
	rm -f program
