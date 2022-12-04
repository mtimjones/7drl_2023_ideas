INC=-I.
CFLAGS=-std=c18
LIB=-lncurses

demo: screen.c headers.h
	gcc $(CFLAGS) $(INC) -o demo screen.c $(LIB)

clean:
	rm -f demo *.o
