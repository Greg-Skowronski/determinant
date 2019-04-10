all: det

det: det.o primlib.o
	gcc -g $^ -o $@ -lm -lSDL -lpthread -lSDL_gfx

.c.o: 
	gcc -g -Wall -pedantic -std=c99 -c -D_REENTRANT $<

primlib.o: primlib.c primlib.h

det.o: det.c primlib.h

clean:
	-rm primlib.o det.o det