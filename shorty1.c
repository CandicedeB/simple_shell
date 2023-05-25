#include "shell.h"

/**
 * stringLen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int stringLen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}

/**
 * _strcmps - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmps(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * beginWIth - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *beginWIth(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * strConcat - concatenates two strings
 * @dest: the destination fender
 * @place: the source fender
 *
 * Return: pointer to destination fender
 */
char *strConcat(char *dest, char *place)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*place)
		*dest++ = *place++;
	*dest = *place;
	return (ret);
}
