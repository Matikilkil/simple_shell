#include "shell.h"


int execute_command(char **args) {
    int status;
	// Fork a child process
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return -1;
    }

    if (child_pid == 0) { // Child process
        if (execvp(args[0], args) == -1) {
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
    } else { // Parent process
       
        waitpid(child_pid, &status, 0);
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
}
