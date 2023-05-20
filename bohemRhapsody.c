#include "shell.h"

/**
 * _puts - Entry point
 * Description: Prints a string to stdout
 * @text: String data type
 * Return: text
 */

void _puts(char *text)
{
	int i = 0;

	while (text[i] != '\0')
	{
		_putchar(text[i]);
		i++;
	}
	_putchar('\n');
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: 1 if true, 0 if false
 * On error, -1 return.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}
