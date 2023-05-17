#include "shell.h"

/**
 * sub_search - searches for substring in string
 * @str: string to search
 * @substr: the substring to find
 *
 * Return: pointer to next character after the substring in the string or NULL
 */

char *sub_search(const char *str, const char *substr)
{
	/* iterate through the substring and check if it matches */
	while (*substr)
	{
		if (*substr++ != *str++)
			return (NULL);
	}
	/* if all characters in the substring match with the string */
	return ((char *)str);
}
