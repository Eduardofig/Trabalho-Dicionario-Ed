all: main2.o AVL.o AVLrec.o
	gcc -std=c99 -g -Wall AVL.o AVLrec.o main2.o -o programTrab -lm

main2.o: main2.c
	gcc -std=c99 -g -c -Wall main2.c

AVL.o: AVL.c
	gcc -std=c99 -g -c -Wall AVL.c

AVLrec.o: AVLrec.c
	gcc -std=c99 -g -c -Wall AVLrec.c

run:
	./programTrab

clean:
	rm -f *.o 
	rm -f programTrab
