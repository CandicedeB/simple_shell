#include "shell.h"

/**
 * _isalpha - checks for alphabetic character
 * @c: character to be checked
 *
 * Return: 1 if c is a letter (lowercase or uppercase), 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * my_deli - checks if character is a delimeter in the shell
 * @c: Character to be checked
 * @limiter: Delimeter string
 * Return: 1 if true, 0 if false
 */
int my_deli(char c, char *limiter)
{
	while (*limiter)
		if (*limiter++ == c)
			return (1);
	return (0);
}