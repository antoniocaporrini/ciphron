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
typedef unsigned int int32;
typedef unsigned long long int int64;
typedef int8 Identifier;

// --- ENUMS ---

// Enumeration for the different types of variables
enum e_type {
    Nothing,
    Int,
    Char,
    String
}; typedef enum e_type Type;

// --- STRUCTS ---

// A struct that can hold any type of value
struct s_variable {
    Type datatype;
    Identifier *name;
    void *value; // <- We should be able to store any type of value here
}; typedef struct s_variable variable; 

// --- MACROS ---
#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $c (char *)
#define $i (int)

// We added parentheses here in case of using an expression
#define newstr(pointer, name, value) do { \
    int8 *_tmp; \
    int16 _tmp2; \
    _tmp2 = length((value)) + 1; \
    if (!_tmp2) { \
        (pointer) = (variable *) 0; \
    } else { \
        _tmp = $1 malloc(_tmp2); \
        if (!_tmp) { \
            (pointer) = (variable *) 0; \
        } else { \
            copy(_tmp, (value), _tmp2); \
            (pointer) = mkvar(String, (name), _tmp); \
            if (!(pointer)) \
                free(_tmp); \
        } \
    } \
} while (0)

#define newvar(datatype, enumtype, pointer, name, value) do { \
    datatype *_tmp = (datatype *)malloc(sizeof(datatype)); \
    if (!_tmp) { \
        (pointer) = (variable *)0; \
    } else { \
        *_tmp = (value); \
        (pointer) = mkvar(enumtype, (name), _tmp); \
        if (!(pointer)) \
            free(_tmp); \
    } \
} while (0)

#define newint(pointer, name, value) newvar(int32, Int, (pointer), (name), (value))
#define newchar(pointer, name, value) newvar(char, Char, (pointer), (name), (value))

// --- PROTOTYPES ---

void mainloop(bool*);
void prompt(void);
int8 *readline(void);
int16 length(int8*);
void copy(int8*, int8*, int16);

// The variable should take a type, an identifier and a value
variable *mkvar(Type,Identifier*,void*);

// What does char** mean?
// It means a pointer to a pointer to a character, often used for arrays of strings.
int main(int,char**);
