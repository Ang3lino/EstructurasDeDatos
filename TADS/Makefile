#	Mi primer makefile :3
all: pro

pro: main.o bst.o 
	gcc -g3 main.o bst.o -o a

main.o: main.c bst.h
	gcc -c main.c

bst.o: bst.c bst.h
	gcc -c bst.c

clean:
	rm -f a *.o
