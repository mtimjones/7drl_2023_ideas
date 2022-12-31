# Makefile for 7drl 2023 ideas

CC=gcc
CFLAGS=-std=c18 -Wall -Werror -Wextra
LIBS= -lncurses -lm

DEPS = headers.h ces.h
OBJS = main.o screen.o time.o messages.o user_input.o game.o map.o select.o player.o ces.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

demo: $(OBJS)
	$(CC) -g -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f demo *.o
