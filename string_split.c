#include "shell.h"


// Function to split a string into tokens based on delimiter
int split_into_tokens(char *str, char **tokens, char *delimiters) {
    int token_count = 0;
    char *token = strtok(str, delimiters);
    while (token != NULL && token_count < MAX_ARGS - 1) {
        tokens[token_count++] = token;
        token = strtok(NULL, delimiters);
    }
    return token_count;
}
