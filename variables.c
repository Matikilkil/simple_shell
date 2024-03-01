#include "shell.h"

void replace_variables(char *command) {
    char *pos;
    while ((pos = strstr(command, "$$")) != NULL) {
        char pid_str[20]; // Assuming process ID fits in 20 characters
        sprintf(pid_str, "%d", getpid());
        strcpy(pos, pid_str);
        strcpy(pos + strlen(pid_str), pos + 2);
    }

    while ((pos = strstr(command, "$?")) != NULL) {
        // Implement $? replacement (return value of the last executed command)
        fprintf(stderr, "Variable $? not implemented\n");
        // For now, just remove the variable
        strcpy(pos, pos + 2);
    }
}
