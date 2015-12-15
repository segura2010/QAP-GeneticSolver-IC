# Modify with your compiler!! (i'm using, so i need to use a special version to use openMP)
CC = g++-5
CFLAGS = -g -O2 -fopenmp
SRC = main.cpp
BIN = bin/gen
BINDIR = bin/

all:
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

clean:
	rm -rf $(BINDIR)*