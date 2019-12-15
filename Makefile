CFLAGS = -g -Wall

all: main.c render.o ship.o bullet.o astroid.o vector.o util.o
	gcc $(CFLAGS) -o astroids main.c render.o ship.o bullet.o astroid.o vector.o util.o -lSDL2 -lm

render.o: 
	gcc $(CFLAGS) -c render.c
ship.o: ship.c 
	gcc $(CFLAGS) -c ship.c 

bullet.o: bullet.c 
	gcc $(CFLAGS) -c bullet.c 

astroid.o: astroid.c
	gcc $(CFLAGS) -c astroid.c

vector.o: vector.c
	gcc $(CFLAGS) -c vector.c 

util.o: util.c
	gcc $(CFLAGS) -c util.c

clean:
	rm astroids *.o
