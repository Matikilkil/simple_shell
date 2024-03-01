#include "shell.h"

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters_read;

    while (1) {
        printf("($) ");
        characters_read = getline(&buffer, &bufsize, stdin);
        if (characters_read == -1) {
            if (feof(stdin)) {
                printf("\n");
                break; // End of file (Ctrl+D)
            } else {
                perror("Error reading input");
                continue;
            }
        }

        // Remove the newline character from the end
        buffer[strcspn(buffer, "\n")] = '\0';

        // Tokenize input into commands separated by ';'
        char *commands[MAX_COMMANDS];
        int command_count = split_into_tokens(buffer, commands, ";");

        // Execute each command sequentially
        for (int i = 0; i < command_count; i++) {
            // Tokenize command into command and arguments
            char *args[MAX_ARGS];
            int arg_count = split_into_tokens(commands[i], args, " ");

            if (arg_count == 0) {
                continue; // Empty command
            }

            if (strcmp(args[0], "cd") == 0) {
                // Handle cd command separately
                char *directory = arg_count > 1 ? args[1] : getenv("HOME");
                if (directory == NULL) {
                    fprintf(stderr, "cd: HOME not set\n");
                    continue;
                } else if (strcmp(directory, "-") == 0) {
                    directory = getenv("OLDPWD");
                    if (directory == NULL) {
                        fprintf(stderr, "cd: OLDPWD not set\n");
                        continue;
                    }
                }

                char cwd[BUFFER_SIZE];
                if (getcwd(cwd, sizeof(cwd)) == NULL) {
                    perror("getcwd");
                    exit(EXIT_FAILURE);
                }

                // Save current directory for future reference
                char oldpwd[BUFFER_SIZE];
                strcpy(oldpwd, cwd);

                // Change directory
                if (chdir(directory) != 0) {
                    perror("cd");
                    continue;
                }

                // Update PWD environment variable
                if (setenv("OLDPWD", cwd, 1) != 0) {
                    perror("setenv");
                    exit(EXIT_FAILURE);
                }
                if (setenv("PWD", oldpwd, 1) != 0) {
                    perror("setenv");
                    exit(EXIT_FAILURE);
                }
            } else {
                // Fork a child process
                pid_t child_pid = fork();

                if (child_pid == -1) {
                    perror("fork");
                    continue;
                }

                if (child_pid == 0) { // Child process
                    if (execvp(args[0], args) == -1) {
                        perror(args[0]);
                        exit(EXIT_FAILURE);
                    }
                } else { // Parent process
                    waitpid(child_pid, NULL, 0);
                }
            }
        }
    }

    free(buffer);
    return EXIT_SUCCESS;
}
