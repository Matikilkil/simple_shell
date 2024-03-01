#include "shell.h"

// Function to execute commands from a file
void execute_commands_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t characters_read;

    while ((characters_read = getline(&line, &len, file)) != -1) {
        // Remove the newline character from the end
        line[strcspn(line, "\n")] = '\0';

        // Ignore everything after '#' character
        char *comment_pos = strchr(line, '#');
        if (comment_pos != NULL) {
            *comment_pos = '\0';
        }

        // Replace variables in the command
        replace_variables(line);

        // Tokenize input into command and arguments
        char *args[BUFFER_SIZE];
        int arg_count = 0;
        char *token = strtok(line, " ");
        while (token != NULL && arg_count < BUFFER_SIZE - 1) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

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

    if (line) {
        free(line);
    }

    fclose(file);
}
