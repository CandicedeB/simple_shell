#include "shell.h"

/**
 * _strdup - Entry point
 * Description: Returns pointer to a newly allocated space
 * @text: Character
 *
 * Return: char
 */

char *_strdup(char *text)
{
	int len = 0, i;
	char *copy;

	if (text == NULL)
	{
		return (NULL);
	}
	while (text[len] != '\0')
	{
		len++;
		/* This determines the length of the input string */
	}

	copy = malloc((len + 1) * sizeof(char));
	/* This allocates memory for the new string */
	if (copy == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < len; i++)
	{
		copy[i] = text[i];
		/* This copies input string to the new string */
	}
	copy[len] = '\0';
	return (copy);
}
