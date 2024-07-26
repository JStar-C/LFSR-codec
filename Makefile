# Author: Joseph Calles

CC = g++
CFLAGS = -g -Wall -Werror -ansi -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
OBJECTS = LFSR.o PhotoMagic.o

all: PhotoMagic

PhotoMagic: PhotoMagic.o LFSR.o
	$(CC) $(CFLAGS) -o PhotoMagic PhotoMagic.o LFSR.o $(LIBS)

PhotoMagic.o: PhotoMagic.cpp LFSR.hpp 
	$(CC) $(CFLAGS) -c PhotoMagic.cpp -o PhotoMagic.o

LFSR.o: LFSR.cpp LFSR.hpp
	$(CC) $(CFLAGS) -c LFSR.cpp -o LFSR.o

clean:
	rm PhotoMagic $(OBJECTS) *~
