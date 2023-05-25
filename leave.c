#include "shell.h"

/**
 **_copyString - performs string copying
 *@dest: the destination string to copy to
 *@place: source string
 *@n: the number of characters to copy
 *Return: the resulting copied string
 */

char *_copyString(char *dest, char *place, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	while (place[a] != '\0' && a < n - 1)
	{
		dest[a] = place[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 **concatenateStrings - performs string concatenation
 *@dest: the first string
 *@place: the second string
 *@n: the maximum number of bytes to be used
 *Return: the resulting concatenated string
 */
char *concatenateStrings(char *dest, char *place, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (place[b] != '\0' && b < n)
	{
		dest[a] = place[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (s);
}

/**
 **strChr - searches for a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: pointer to the memory area of the found character in the string (s)
 */

char *strChr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}