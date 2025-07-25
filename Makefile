# Use C23 standard (recognized as 'c2x' in GCC 15+ and Clang), remove if not needed
flags=-O2 -Wall -std=c2x 
ldflags=-lbu

.PHONY: all clean

all: clean ciphron

ciphron: ciphron.o
	cc $(flags) $^ -o $@ $(ldflags)

ciphron.o: ciphron.c ciphron.h
	cc $(flags) -c $<

clean:
	rm -f *.o ciphron