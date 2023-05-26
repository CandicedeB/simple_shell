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

	if (!s) /* make sure input string is empty or NULL */
		return (0);
	/* Loop through the string until reaching the null-terminating character */
	while (*s++)
		a++; /* Every time a character is met, the variable "a" is increased */
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
		/* Check if the characters at the current positions are different */
		if (*s1 != *s2)
			return (*s1 - *s2); /* difference between ASCII values of characters */
		s1++; /* Move to following character in s1 */
		s2++; /* move to following character in s2 */
	}
	if (*s1 == *s2)
		return (0); /* return 0 to indicate that the strings are equal */
	else
		return (*s1 < *s2 ? -1 : 1); /* if not return -1 s1 is less than s2, or 1 */
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
	while (*viens) /* Iterate through the characters of the viens string */
		if (*viens++ != *heart++)
			return (NULL); /* If they are different, return NULL to indicate no match */
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

	while (*dest) /* Move pointer "dest" to the end of the destination string */
		dest++;
	/* Copy characters from the "place" string to the end of "dest" string */
	while (*place)
		*dest++ = *place++;
	*dest = *place;
	return (ret); /* the starting address of the concatenated string */
}
