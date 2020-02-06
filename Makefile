DEBUGFLAGS = -g -W -Wall
BUILDFLAGS = $(DEBUGFLAGS)
CC = gcc

all : img2tt

img2tt: img2tt.o
	$(CC) -g -o img2tt img2tt.o -lm -lIL -lILU

img2tt.o: img2tt.c
	$(CC) $(BUILDFLAGS) -c -o img2tt.o img2tt.c
