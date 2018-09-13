input:
	gcc -c input.c

main:
	g++ -c main.cpp

all: input main
	g++ input.o main.o -o main

clean:
	rm input.o main
