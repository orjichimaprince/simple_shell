#include "simple_shell.h"

/**
 * error_file - handle error
 *
 * @chaine: user's chain
 * @i: count
 * @argv: Argument value passes at the beginning
 * @nerr: The number of the error that occurs
 *
 * Return: 127
 */
int error_file(char *chaine, int i, char *argv[], int nerr)
{
	int length;
	char *number, *str;
	char *merr[3] = {	": not found\n",
						": File name too long\n",
						": Permission denied\n"};

	number = int_to_string(i);
	length = _strlen(argv[0]) + _strlen(chaine) + _strlen(number);
	length +=  _strlen(merr[nerr]) + 4;
	str = malloc(sizeof(char) * length + 1);
	*str = '\0';
	str = _strcat(str, argv[0]);
	str = _strcat(str, ": ");
	str = _strcat(str, number);
	str = _strcat(str, ": ");
	str = _strcat(str, chaine);
	str = _strcat(str, merr[nerr]);
	str[length] = '\0';

	write(STDERR_FILENO, str, length);

	free(number);
	free(str);
	return (127);
}

/**
 * int_to_string - Convert an int to string
 *
 * @i: The integer needed to convert
 *
 * Return: str or NULL if the malloc failled
 */
char *int_to_string(int i)
{
	int power = 10, loop = 1;
	unsigned int number;
	char *str;

	if (i < 0)
		number = i * (-1);
	else
		number = i;

	while ((number / power) > 0)
	{
		power *= 10;
		loop++;
	}

	str = malloc(sizeof(char) * loop + 1);
	if (str == NULL)
		return (NULL);
	str[loop] = '\0';
	loop--;
	while (number > 0)
	{
		str[loop] = number % 10 + '0';
		number /= 10;
		loop--;
	}

	return (str);
}
