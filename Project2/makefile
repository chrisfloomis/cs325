CFLAGS = -Wall -fpic -lm -std=c99 -w

all: main.c
	gcc -o program main.c $(CFLAGS)
	./program CoinW16.txt
				
clean:
	rm -f program
