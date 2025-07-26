# Use C23 standard (recognized as 'c2x' in GCC 13+ and Clang), remove if not needed
flags=-O2 -Wall -std=c2x

.PHONY: all clean

# Always rebuild everything from scratch
all: clean ciphron

common.o: common.c common.h
	cc $(flags) -c $<

# Rule to build the ciphron executable
ciphron: ciphron.o common.o
	cc $(flags) $^ -o $@

# Rule to build the object file ciphron.o
ciphron.o: ciphron.c ciphron.h
	cc $(flags) -c ciphron.c

# Clean up object files and binary
clean:
	rm -f *.o ciphron
