all: add-nbo

add-nbo: add-nbo.o 
	gcc -g -o add-nbo add-nbo.o

add-nbo.o: add-nbo.c
	gcc -g -c -o add-nbo.o add-nbo.c

clean:
	rm -f add-nbo *.o
