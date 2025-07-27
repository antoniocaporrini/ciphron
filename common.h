/* common.h */

// Unsigned means the value cannot be negative, so it can only be 0 or positive.
typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;
typedef int8 Identifier;

#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $c (char *)
#define $i (int)

#define dtype(e) _Generic((e), \
    int32: "int32", \
    char: "char", \
    default: "", \
    int: "int", \
    char*: "char*", \
    int8*: "string" \
) 

/* #define showtype(e) printf("%s :: (%s)\n", # e, dtype((e))); */



