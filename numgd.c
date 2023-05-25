#include "shell.h"

/**
 * copyString  - copies a string
 * @dest: the place
 * @place: the source
 *
 * Return: pointer to end point
 */
char *copyString (char *dest, char *place)
{
	int a = 0;

	if (dest == place || place == 0)
		return (dest);
	while (place[a])
	{
		dest[a] = place[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}

/**
 * _strdupsd - duplicates a string
 * @txt: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdupsd(const char *txt)
{
	int length = 0;
	char *ret;

	if (txt == NULL)
		return (NULL);
	while (*txt++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--txt;
	return (ret);
}

/**
 *putin - prints an input string
 *@txt: the string to be printed
 *
 * Return: Nothing
 */
void putin(char *txt)
{
	int a = 0;

	if (!txt)
		return;
	while (txt[a] != '\0')
	{
		_putchar(txt[a]);
		a++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int a;
	static char buffed[WRITE_BUF_SIZE];

	if (c == BUFFER_FLUSHER || a >= WRITE_BUF_SIZE)
	{
		write(1, buffed, a);
		a = 0;
	}
	if (c != BUFFER_FLUSHER)
		buffed[a++] = c;
	return (1);
}
