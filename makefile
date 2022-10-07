rns: node.o rns.o
	gcc node.o rns.o -o rns
rns.o : node.h node.c
	gcc -Wall -c rns.c 
node.o : node.c node.h utilities.h
	gcc -Wall -c node.c 
clean:
	rm -f *.o rns