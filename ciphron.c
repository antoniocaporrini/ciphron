/* ciphron.c */
#include "ciphron.h"
#include "common.h"

// --- UTILITY FUNCTIONS ---

// It will take a destination, a source, and a size
void copy(int8 *dst, int8 *src, int16 size) {
    int8 *dptr = dst;
    int8 *sptr = src;
    int16 n;
    for (n = size - 1; n && *sptr; n--, dptr++, sptr++)
        *dptr = *sptr;
    *++dptr = 0;
}

// Function to set all bytes of a string to zero
void zero(int8 *str, int16 size) {
    int8 *p;
    int16 n;
    for (n=0, p=str; n<size; n++, p++)
        *p = 0;
}

// Function to calculate the length of a string
int16 length(int8 *str) {
    int16 n;
    int8 *p;
    if (!str) return 0;
    for (n=0, p=str; *p; n++, p++);
    return n;
}

// --- VARIABLE CONSTRUCTORS ---

// Constructor function for making a variable
variable *mkvar(Type type, Identifier *ident, void* value) {
    variable *p;
    int16 size;
    if (!type || !ident || !value)
        // Return NULL if any of the parameters are invalid
        return (variable *)0; 
    size = sizeof(struct s_variable);
    p = (variable *)malloc($i size);
    if (!p) 
        // If memory allocation fails, return NULL
        return (variable *)0;
    zero($1 p, size);
    p->datatype = type;
    p->name = ident;
    p->value = value;
    return p;
}

// --- INPUT/OUTPUT FUNCTIONS ---

// We'll read the read line from the standard input and remove the newline character
int8 *readline() {
    int8 *p, *ret;
    int16 size;
    int8 buf[128];
    zero(buf, 127);
    size = $2 read(0, $c &buf, 127);
    if (size > 0) {
        buf[size - 1] = '\0'; // Sostituisce il \n con \0 se c'è
        // Rimuovi anche eventuali altri \r o \n residui (opzionale)
        for (p = buf; *p; p++) {
            if (*p == '\n' || *p == '\r') {
                *p = '\0';
                break;
            }
        }
    }
    if (!(*buf))
        return $1 0; // If the buffer is empty, return NULL
    ret = (int8 *)malloc(size); // Allocate memory for the string
    if (!ret) 
        return $1 0;
    zero(ret, size);
    copy(ret, buf, size); // Copy the string to the allocated memory
    return ret;
}

void prompt() {
    printf("ciphron> ");
    fflush(stdout);
}

// --- MAIN LOGIC ---

void mainloop(bool *cpntr) {
    int8 *cmd;
    prompt();
    cmd = readline();
    if (cmd) {
        if (!strcmp($c cmd, "exit")) {
            *cpntr = false;
        } else if (!strcmp($c cmd, "x")) {
            printf("42\n");
        } else if (!strcmp($c cmd, "Dev")) {
            printf("Antonio\n");
        } else {
            printf("Unknown variable or command.\n");
        }
        free(cmd);
    }
}

int main(int argc, char *argv[]) {
    bool continuation;
    bool *cpntr;
    continuation = true;
    cpntr = &continuation;
    while (continuation) {
        mainloop(cpntr);
    }
    return 0;
}
