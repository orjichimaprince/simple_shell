#include "simple_shell.h"

/**
 * separate_av - separate the words
 *
 * @str: The String we want to know the words
 * @sep: The separator we destroy
 *
 * Return: The array of string
 */
char **separate_av(char *str, char *sep)
{
	char *y, **j;
	int i = 0, length;

	if (str == NULL)
		return (NULL);

	length = count_word(str, sep);
	y = strtok(str, sep);

	j = _calloc(sizeof(char *), (length) + 1);

	while (y != NULL)
	{
		j[i++] = _strdup(y);
		y = strtok(NULL, sep);
	}

	if (j[0] == NULL)
	{
		free_separate_av(j);
		return (NULL);
	}

	return (j);
}

/**
 * free_separate_av - Free the memory alocated by separate_av
 *
 * @str: The array of string
 */
void free_separate_av(char **str)
{
	int i = 0;

	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
