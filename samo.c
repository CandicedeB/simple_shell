#include "shell.h"

/**
 *eputin - prints an input string
 * @txt: the string to be printed
 *
 * Return: Nothing
 */
void eputin(char *txt)
{
	int a = 0;

	if (!txt)
		return;
	while (txt[a] != '\0')
	{
		eputword(txt[a]);
		a++;
	}
}

/**
 * eputword - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int eputword(char c)
{
	static int a;
	static char buffed[WRITE_BUF_SIZE];

	if (c == BUFFER_FLUSHER || a >= WRITE_BUF_SIZE)
	{
		write(2, buffed, a);
		a = 0;
	}
	if (c != BUFFER_FLUSHER)
		buffed[a++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int a;
	static char buffed[WRITE_BUF_SIZE];

	if (c == BUFFER_FLUSHER || a >= WRITE_BUF_SIZE)
	{
		write(fd, buffed, a);
		a = 0;
	}
	if (c != BUFFER_FLUSHER)
		buffed[a++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @txt: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *txt, int fd)
{
	int a = 0;

	if (!txt)
		return (0);
	while (*txt)
	{
		a += _putfd(*txt++, fd);
	}
	return (a);
}
