/* ciphron.c */
#include "ciphron.h"
#include "common.h"

// --- UTILITY FUNCTIONS ---

#define MAX_VARS 100

typedef struct {
    char name[32];
    int value;
} int_var;

int_var int_vars[MAX_VARS];
int int_var_count = 0;

void add_int_var(const char* name, int value) {
    if (int_var_count >= MAX_VARS) {
        printf("Too many variables!\n");
        return;
    }
    strncpy(int_vars[int_var_count].name, name, 31);
    int_vars[int_var_count].name[31] = '\0';
    int_vars[int_var_count].value = value;
    int_var_count++;
}

int* find_int_var(const char* name) {
    for (int i = 0; i < int_var_count; i++) {
        if (strcmp(int_vars[i].name, name) == 0)
            return &int_vars[i].value;
    }
    return NULL;
}

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
        } else if (strncmp($c cmd, "int ", 4) == 0) {
            char varname[32];
            int value;
            if (sscanf($c cmd, "int %31s = %d;", varname, &value) == 2 ||
                sscanf($c cmd, "int %31s = %d", varname, &value) == 2) {
                size_t len = strlen(varname);
                if (varname[len-1] == ';') varname[len-1] = 0;
                add_int_var(varname, value);
                printf("Variable '%s' set to %d\n", varname, value);
            } else {
                printf("Syntax error! Usage: int nome = valore;\n");
            }
        } else if (strncmp($c cmd, "print ", 6) == 0) {
            char varname[32];
            if (sscanf($c cmd, "print %31s", varname) == 1) {
                size_t len = strlen(varname);
                if (varname[len-1] == ';') varname[len-1] = 0;
                int* value = find_int_var(varname);
                if (value) {
                    printf("%s = %d\n", varname, *value);
                } else {
                    printf("Variable '%s' not found\n", varname);
                }
            } else {
                printf("Syntax error! Usage: print name;\n");
            }
        } else {
            printf("Unknown command!\n");
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
