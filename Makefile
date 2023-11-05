build: main.o reading.o calculations.o tree.o
	gcc -Wall main.o reading.o calculations.o tree.o -o quadtree

main.o: main.c
	gcc -Wall -c main.c

reading.o: reading.c
	gcc -Wall -c reading.c
	
calculations.o: calculations.c
	gcc -Wall -c calculations.c

tree.o: tree.c
	gcc -Wall -c tree.c

clean:
	rm *.o && rm quadtree