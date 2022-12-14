INC=-I.
CFLAGS=-std=c18 -Wall -Werror -Wextra
LIB=-lncurses

demo: main.c screen.c time.c messages.c user_input.c game.c map.c select.c headers.h
	gcc $(CFLAGS) $(INC) -o demo screen.c main.c time.c messages.c user_input.c game.c map.c select.c $(LIB)

clean:
	rm -f demo *.o
