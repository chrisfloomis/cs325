CFLAGS = -Wall -fpic -lm -std=c99
FILE = MSS_Results.txt

# enum_MSA.o: msa.h enum_MSA.c
		# gcc -c enum_MSA.c -g  $(CFLAGS)
			
# betterEnum_MSA.o: msa.h betterEnum_MSA.c
		# gcc -c betterEnum_MSA.c -g  $(CFLAGS)
			
# divConq_MSA.o: msa.h divConq_MSA.c
		# gcc -c divConq_MSA.c -g  $(CFLAGS)
			
# linear_MSA.o: msa.h linear_MSA.c
		# gcc -c linear_MSA.c -g  $(CFLAGS)

# msa: enum_MSA.o betterEnum_MSA.o divConq_MSA.o linear_MSA.o main.c
		# gcc -o msa main.c -g enum_MSA.o betterEnum_MSA.o divConq_MSA.o linear_MSA.o $(CFLAGS)

all: main.c
	gcc -o program main.c $(CFLAGS)
	./program MSS_TestProblems.txt
	echo "" >> $(FILE)
	echo "" >> $(FILE)
	echo "Next Algorithm goes here" >> $(FILE)
				
clean:
	rm -f MSS_Results.txt program
