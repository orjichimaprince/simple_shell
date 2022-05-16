#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

extern char **environ;

/**
 * struct linke_path -Do a linked list for environment variable PATH
 *
 * @value: The value of the PATH
 * @next: The next node
 *
 */
typedef struct linked_path
{
	char *value;
	struct linked_path *next;
} path_t;

/**
 * struct linked_env - Do a linked list for all environment variables
 *
 * @name: Name of the current environment variable
 * @value: Value of the current environment variable
 * @next: The next environment variable
 *
 */
typedef struct linked_env
{
	char *name;
	char *value;
	struct linke_env *next;
} env_t;

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
int _putchar(char c);
void _puts(char *str);
unsigned int nbr_spaces(char *s);
char **stringToTokens(char *str);
char **strtow(char *str, char sep)
int _strcmp(char *s1, char *s2)
void free_node(path_t *head);

#endif
