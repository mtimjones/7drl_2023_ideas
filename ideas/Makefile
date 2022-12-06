INC=-I.
CFLAGS=-std=c18
LIB=-lncurses

demo: main.c screen.c time.c messages.c headers.h
	gcc $(CFLAGS) $(INC) -o demo screen.c main.c time.c messages.c $(LIB)

clean:
	rm -f demo *.o
