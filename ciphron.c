/* ciphron.c */
#include "ciphron.h"
#include "common.h"

// --- UTILITY FUNCTIONS ---
#define MAX_VARS 100
#define MAX_STRING_VARS 100

typedef struct {
    char name[32];
    int value;
} int_var;

typedef struct {
    char name[32];
    char value[128];
} str_var;

str_var str_vars[MAX_STRING_VARS];
int str_var_count = 0;

int_var int_vars[MAX_VARS];
int int_var_count = 0;

// Function to add an integer variable
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

// Function to find an integer variable by name
int* find_int_var(const char* name) {
    for (int i = 0; i < int_var_count; i++) {
        if (strcmp(int_vars[i].name, name) == 0)
            return &int_vars[i].value;
    }
    return NULL;
}

// Function to add a string variable
void add_str_var(const char* name, const char* value) {
    if (str_var_count >= MAX_STRING_VARS) {
        printf("Too many string variables!\n");
        return;
    }
    // Ensure the name and value fit within the limits
    strncpy(str_vars[str_var_count].name, name, 31);
    str_vars[str_var_count].name[31] = '\0';
    // Ensure the value is null-terminated and fits within 128 characters
    strncpy(str_vars[str_var_count].value, value, 127);
    str_vars[str_var_count].value[127] = '\0';
    str_var_count++;
}

// Function to find a string variable by name
const char* find_str_var(const char* name) {
    for (int i = 0; i < str_var_count; i++) {
        if (strcmp(str_vars[i].name, name) == 0)
            return str_vars[i].value;
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


// --- INPUT/OUTPUT FUNCTIONS ---

// We'll read the read line from the standard input and remove the newline character
int8 *readline() {
    int8 *p, *ret;
    int16 size;
    int8 buf[128];
    zero(buf, 127);
    size = $2 read(0, $c &buf, 127);
    if (size > 0) {
        buf[size - 1] = '\0'; 
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

void show_intro() {
    printf("\n");
    printf("  ____ _       _                     \n");
    printf(" / ___(_)_ __ | |__  _ __ ___  _ __  \n");
    printf("| |   | | '_ \\| '_ \\| '__/ _ \\| '_ \\ \n");
    printf("| |___| | |_) | | | | | | (_) | | | |\n");
    printf(" \\____|_| .__/|_| |_|_|  \\___/|_| |_|\n");
    printf("        |_|                          \n");
    printf("\n");
    printf("Ciphron — a tiny C-style REPL.\n");
    printf("Developed by Antonio Caporrini.\n\n");
    printf("Welcome to Ciphron — introspection for your code.\n");
}

void prompt() {
    printf("ciphron> ");
    fflush(stdout); // Print the prompt
}

// --- MAIN LOGIC ---

void mainloop(bool *cpntr) {
    int8 *cmd;
    prompt();
    cmd = readline();
    if (cmd) {
        // Exit the program
        if (!strcmp($c cmd, "exit")) {
            *cpntr = false;

        // Haskell-like command: :t varname (prints variable type)
        } else if (strncmp($c cmd, ":t ", 3) == 0) {
            char varname[32];
            if (sscanf($c cmd, ":t %31s", varname) == 1) {
                size_t len = strlen(varname);
                if (varname[len-1] == ';') varname[len-1] = 0;
                int* value = find_int_var(varname);
                if (value) {
                    printf("%s :: int\n", varname);
                } else {
                    const char* svalue = find_str_var(varname);
                    if (svalue) {
                        printf("%s :: string\n", varname);
                    } else {
                        printf("Variable '%s' not found\n", varname);
                    }
                }
            } else {
                printf("Usage: :t varname\n");
            }

        // Integer variable declaration
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
                printf("Syntax error! Usage: int name = value;\n");
            }

        // String variable declaration
        } else if (strncmp($c cmd, "string ", 7) == 0) {
            char varname[32];
            char value[128];
            // Accepts both with and without ;, with or without ""
            if (sscanf($c cmd, "string %31s = \"%127[^\"]\";", varname, value) == 2 ||
                sscanf($c cmd, "string %31s = \"%127[^\"]\"", varname, value) == 2 ||
                sscanf($c cmd, "string %31s = %127s;", varname, value) == 2 ||
                sscanf($c cmd, "string %31s = %127s", varname, value) == 2) {
                size_t len = strlen(varname);
                if (varname[len-1] == ';') varname[len-1] = 0;
                // Removes trailing ; or quote if present
                size_t vlen = strlen(value);
                if (vlen > 0 && value[vlen-1] == ';') value[vlen-1] = 0;
                add_str_var(varname, value);
                printf("Variable '%s' set to \"%s\"\n", varname, value);
            } else {
                printf("Syntax error! Usage: string name = \"value\";\n");
            }

        // Print variable value
        } else if (strncmp($c cmd, "print ", 6) == 0) {
            char varname[32];
            if (sscanf($c cmd, "print %31s", varname) == 1) {
                size_t len = strlen(varname);
                if (varname[len-1] == ';') varname[len-1] = 0;
                int* value = find_int_var(varname);
                if (value) {
                    printf("%s = %d\n", varname, *value);
                } else {
                    const char* svalue = find_str_var(varname);
                    if (svalue) {
                        printf("%s = \"%s\"\n", varname, svalue);
                    } else {
                        printf("Variable '%s' not found\n", varname);
                    }
                }
            } else {
                printf("Syntax error! Usage: print name;\n");
            }

        // Unknown command handler
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
    show_intro();
    cpntr = &continuation;
    while (continuation) {
        mainloop(cpntr);
    }
    return 0;
}
