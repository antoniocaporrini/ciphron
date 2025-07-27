/* ciphron.h */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>

#pragma once
#pragma GCC diagnostic ignored "-Wstringop-truncation"
#pragma GCC diagnostic ignored "-Wformat-truncation="
#pragma GCC diagnostic push

// --- TYPEDEFS ---

// Unsigned means the value cannot be negative, so it can only be 0 or positive.
typedef unsigned char int8;
typedef unsigned short int int16;

// --- FUNCTION PROTOTYPES ---

// Prints the Ciphron intro banner to the screen
void show_intro(void);

// Prints the command prompt (e.g., ciphron>)
void prompt(void);

// Reads a line from standard input and removes the newline character
int8 *readline(void);

// Returns the length of a string
int16 length(int8*);

// Copies size bytes from src to dst (with null termination)
void copy(int8*, int8*, int16);

// The main REPL loop, takes a pointer to a boolean that controls continuation
void mainloop(bool*);

// The program's main entry point
int main(int, char**);