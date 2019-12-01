CFLAGS = -g -Wall

all: main.c render.o ship.o bullet.o vector.o 
	gcc $(CFLAGS) -o astroids main.c render.o ship.o bullet.o vector.o -lSDL2 -lm

render.o: 
	gcc $(CFLAGS) -c render.c
ship.o: ship.c 
	gcc $(CFLAGS) -c ship.c 

bullet.o: bullet.c 
	gcc $(CFLAGS) -c bullet.c 

vector.o: vector.c
	gcc $(CFLAGS) -c vector.c 

clean:
	rm astroids *.o
