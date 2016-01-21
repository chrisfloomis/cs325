CFLAGS = -Wall -fpic -lm

enum_MSA.o: msa.h enum_MSA.c
	gcc -c enum_MSA.c -g  $(CFLAGS)
	
betterEnum_MSA.o: msa.h betterEnum_MSA.c
	gcc -c betterEnum_MSA.c -g  $(CFLAGS)
	
divConq_MSA.o: msa.h divConq_MSA.c
	gcc -c divConq_MSA.c -g  $(CFLAGS)
	
linear_MSA.o: msa.h linear_MSA.c
	gcc -c linear_MSA.c -g  $(CFLAGS)

msa: enum_MSA.o betterEnum_MSA.o divConq_MSA.o linear_MSA.o main.c
	gcc -o msa main.c -g enum_MSA.o betterEnum_MSA.o divConq_MSA.o linear_MSA.o $(CFLAGS)

all: msa

clean:
	rm -f *.o msa.exe msa *.gcov *.gcda *.gcno *.so
