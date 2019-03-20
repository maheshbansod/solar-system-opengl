CC=gcc
CFLAGS=-lm -lGL -lGLU -lglut
DEPS=values.h structs.h headers.h
SRCS=solarsystem.c helperfuncs.c systemfuncs.c drawers.c
OBJS=$(SRCS:.c=.o)

all: $(SRCS) $(OBJS) solarsystem

%.o: %.c $(DEPS)
	$(CC) -c $(SRCS)

solarsystem: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS)
