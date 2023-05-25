#include "shell.h"

/**
 * invlove - determines if the shell is in interactive mode
 * @data:  pointer to struct
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int invlove(info_t *data)
{
	return (isatty(STDIN_FILENO) && data->readingFd <= 2);
}

/**
 * we_believe - determines if a character is a delimiter
 * @c: the character to be checked
 * @limitme: the string containing delimiters
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int we_believe(char c, char *limitme)
{
	while (*limitme)
		if (*limitme++ == c)
			return (1);
	return (0);
}

/**
 *isAlphabetic - checks if a character is alphabetic
 *@c: the character to be checked
 *Return: 1 if the character is alphabetic, 0 otherwise
 */

int isAlphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *convertToInteger - converts a string to an integer
 *@s: string converted
 *Return: 0 if there are no num in the string, the converted number otherwise
 */

int convertToInteger(char *s)
{
	int a, tive = 1, onOff = 0, outta;
	unsigned int answer = 0;

	for (a = 0;  s[a] != '\0' && onOff != 2; a++)
	{
		if (s[a] == '-')
			tive *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			onOff = 1;
			answer *= 10;
			answer += (s[a] - '0');
		}
		else if (onOff == 1)
			onOff = 2;
	}

	if (tive == -1)
		outta = -answer;
	else
		outta = answer;

	return (outta);
}
