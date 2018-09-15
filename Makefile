all: input control gopigo main
	gcc input.o control.o gopigo.o main.o -o main 

input:
	gcc -c input.c

gopigo:
	gcc -c gopigo.c

control:
	gcc -c control.c

main:
	gcc -c main.c

clean:
	rm *.o main
