all: main.o AVL.o AVLrec.o
	gcc -std=c99 -g -Wall AVL.o AVLrec.o main.o -o programTrab -lm

main.o: main.c
	gcc -std=c99 -g -c -Wall main.c

AVL.o: AVL.c
	gcc -std=c99 -g -c -Wall AVL.c

AVLrec.o: AVLrec.c
	gcc -std=c99 -g -c -Wall AVLrec.c

run:
	./programTrab

clean:
	rm -f *.o 
	rm -f programTrab
