all: input main
	gcc input.o main.o -o main

input:
	gcc -c input.c

main:
	gcc -c main.c

clean:
	rm *.o main
