#include "shell.h"

typedef struct {
    char *name;
    char *value;
} Alias;

Alias aliases[MAX_ALIASES];
int alias_count = 0;

/** find_alias_index - Function to find the index of an alias by name
 * @name: pointer
 * Return: -1
 */
int find_alias_index(const char *name)
{
	int i;

	for (i = 0; i < alias_count; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			return (i);
		}
	}
	return (-1);
}

/** print_aliases - Function to print all aliases or specific aliases
 * @names: pointer
 * @name_count: parameter
 * Return:0
 */
void print_aliases(char *names[], int name_count)
{
	int i, index;

	if (name_count == 0) {
        // Print all aliases
        for (i = 0; i < alias_count; i++) {
            printf("%s='%s'\n", aliases[i].name, aliases[i].value);
        }
    } else {
        // Print specific aliases
        for (i = 0; i < name_count; i++) {
            index = find_alias_index(names[i]);
            if (index != -1) {
                printf("%s='%s'\n", aliases[index].name, aliases[index].value);
            }
        }
    }
}

// Function to define or modify aliases
void define_aliases(char *definitions[], int definition_count)
{
	int i, index;
	char *name;
	char *value;

    for (i = 0; i < definition_count; i++) {
        name = strtok(definitions[i], "=");
        value = strtok(NULL, "=");

        // Check if the alias already exists
        index = find_alias_index(name);
        if (index != -1) {
            // Modify existing alias
            free(aliases[index].value);
            aliases[index].value = strdup(value);
        } else {
            // Define new alias
            if (alias_count >= MAX_ALIASES) {
                fprintf(stderr, "Maximum number of aliases exceeded\n");
                return;
            }
            aliases[alias_count].name = strdup(name);
            aliases[alias_count].value = strdup(value);
            alias_count++;
        }
    }
}
