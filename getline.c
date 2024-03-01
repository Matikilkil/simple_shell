#include "shell.h"


char *custom_getline(void) {
    static char buffer[BUFFER_SIZE];
    static int index = 0;
    int c;
    char *line = NULL;
    int line_size = 0;

    while (1) {
        if (index == 0) {
            // Refill buffer if it's empty
            int bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            if (bytes_read <= 0) {
                // No more input or error
                return NULL;
            }
            index = 0;
        }

        c = buffer[index++];
        if (c == '\n' || c == EOF) {
            // End of line or end of file
            if (line_size == 0 && c == EOF) {
                // No characters read and EOF encountered
                return NULL;
            }
            if (line_size > 0 && line[line_size - 1] == '\r') {
                // Remove carriage return if present
                line[line_size - 1] = '\0';
            }
            line[line_size] = '\0'; // Null-terminate the string
            return line;
        } else {
            // Append character to line
            line = realloc(line, line_size + 2); // +2 for the new char and null-terminator
            if (!line) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            line[line_size++] = c;
        }
    }
}
