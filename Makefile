all: main
	gcc input.o control.o gopigo.o main.o -o main 

main: input
	gcc -c main.c

input: control 
	gcc -c input.c

control: gopigo
	gcc -c control.c

gopigo:
	gcc -c gopigo.c

clean:
	rm *.o main
