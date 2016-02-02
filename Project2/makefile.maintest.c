CFLAGS = -Wall -fpic -lm -std=c99

all: maintest.c
	gcc -o program maintest.c $(CFLAGS)
	./program
				
clean:
	rm -f program
