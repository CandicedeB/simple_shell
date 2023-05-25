#include "shell.h"

/**
 **_strncpy - Copies string in shell
 *@dtsin: final destination string to be copied to
 *@locat: the string source
 *@n: the num of chars to be copied
 *Return: oncatenated string
 */
char *_strncpy(char *dtsin, char *locat, int n)
{
	int i, j;
	char *s = dtsin;

	i = 0;
	while (locat[i] != '\0' && i < n - 1)
	{
		dtsin[i] = locat[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dtsin[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dtsin: the first string
 *@locat: the second string
 *@n: the num of bytes used
 *Return: Concatenated string in shell
 */
char *_strncat(char *dtsin, char *locat, int n)
{
	int i, j;
	char *s = dtsin;

	i = 0;
	j = 0;
	while (dtsin[i] != '\0')
		i++;
	while (locat[j] != '\0' && j < n)
	{
		dtsin[i] = locat[j];
		i++;
		j++;
	}
	if (j < n)
		dtsin[i] = '\0';
	return (s);
}

/**
 **_strchr - Finds a char in a string within shell
 *@s: the string to be parsed within the shell
 *@c: the character we are to find
 *Return: Pointer to the mem area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}