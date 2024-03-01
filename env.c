#include "shell.h"


/** print_environment -  Function to print the environment variables
 */
void print_environment()
{
	char **env;
    extern char **environ;
    for (env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}
