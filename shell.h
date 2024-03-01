#ifndef SHELL_H
#define SHELL_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX_ALIASES 64


int find_alias_index(const char *name);
void print_aliases(char *names[], int name_count);
void define_aliases(char *definitions[], int definition_count);
void replace_variables(char *command);
void execute_commands_from_file(const char *filename);
int main(int argc, char *argv[]);
char *custom_getline(void);
int execute_command(char **args);
int split_into_tokens(char *str, char **tokens, char *delimiters);
int file_exists(const char *filename);

#endif /*SHELL_H*/
