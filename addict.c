#include "shell.h"

/**
 * invlove - determines if the shell is in interactive mode
 * @data:  pointer to struct
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int invlove(info_t *data)
{
	/* Verify that the file descriptor is within range and */
	/* that the shell is reading from a terminal.*/
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
	/* Make sure the character corresponds to one of the string's delimiters */
	while (*limitme)
		if (*limitme++ == c)
			return (1);
	return (0); /* 0 will be returned if the character is not a delimiter */
}

/**
 *isAlphabetic - checks if a character is alphabetic
 *@c: the character to be checked
 *Return: 1 if the character is alphabetic, 0 otherwise
 */

int isAlphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1); /* the characters are alphabetical */
	else
		return (0); /* The characters are not alphabetical */
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
	/* until the string reaches a null terminator or onOff is 2 */
	/* iterate through the string */
	for (a = 0;  s[a] != '\0' && onOff != 2; a++)
	{
		if (s[a] == '-')
			tive *= -1; /* If a '-' appears, change the number's sign */

		if (s[a] >= '0' && s[a] <= '9')
		{
			onOff = 1; /* Tell the user that genuine digits have been located */
			answer *= 10;
			answer += (s[a] - '0'); /* Transform a character into a digit */
			/* then add up the value */
		}
		else if (onOff == 1)
			onOff = 2; /* Show that the string's numerical portion has ended */
	}
	/* Apply the sign to the transformed integer's final value */
	if (tive == -1)
		outta = -answer;
	else
		outta = answer;

	return (outta); /* Provide the translated integer value back */
}
