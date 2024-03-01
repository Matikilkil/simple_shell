#include "shell.h"


// Function to check if a file exists
int file_exists(const char *filename) {
    return access(filename, F_OK) != -1;
}
