CC=gcc
CFLAGS=-lm -lGL -lGLU -lglut

solarsystem: solarsystem.c
	$(CC) solarsystem.c $(CFLAGS)
