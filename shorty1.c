#include "shell.h"

/**
 * stringLen - length of a string
 * @s: string
 *
 * Return: integer len of string
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
 * _strcmps - performs lexicogarphic comparison of two strings.
 * @s1: the 1st strang
 * @s2: the 2nd strang
 *
 * Return: -ve if s1 < s2, +ve if s1 > s2, zero if s1 == s2
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
 * beginWith - checks if viens starts with heart
 * @heart: string to search
 * @viens: the substring to find
 *
 * Return: address of next char of heart or NULL
 */
char *beginWith(const char *heart, const char *viens)
{
	while (*viens)
		if (*viens++ != *heart++)
			return (NULL);
	return ((char *)heart);
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
