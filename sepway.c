#include "shell.h"

/**
 * _separator - checks if character is a separator
 * @c: the character to check
 * @separator: the separator string
 *
 * Return: 1 if true, 0 if false
 */

int _separator(char c, char *separator)
{
	/* Loop through the separator string */
	while (*separator)
	{
		/* If the current character matches the separator, return true */
		if (*separator == c)
			return (1);
		separator++;
	}
	/* If no match was found, return false */
	return (0);
}
