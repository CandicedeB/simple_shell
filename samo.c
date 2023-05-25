#include "shell.h"

/**
 *eputin - Displays an input string
 * @txt: the string to be displayed
 * Return: none
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
 * eputword - Outputs the character c to stderr
 * @c: The character to be outputted
 *
 * Return: On success 1.
 * On error, returns -1 and sets errno accordingly.
 */
int eputword(char c)
{
	static int a;
	static char buffed[WRITE_BUFFER];

	if (c == BUFFER_FLUSHER || a >= WRITE_BUFFER)
	{
		write(2, buffed, a);
		a = 0;
	}
	if (c != BUFFER_FLUSHER)
		buffed[a++] = c;
	return (1);
}

/**
 * putFd - Writes the character c to the specified file descriptor
 * @c: The  character to be written
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, returns -1 and sets errno accordingly.
 */
int putFd(char c, int fd)
{
	static int a;
	static char buffed[WRITE_BUFFER];

	if (c == BUFFER_FLUSHER || a >= WRITE_BUFFER)
	{
		write(fd, buffed, a);
		a = 0;
	}
	if (c != BUFFER_FLUSHER)
		buffed[a++] = c;
	return (1);
}

/**
 *putsFdk - Writes the input string to the specified file descriptor
 * @txt: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 * On error, returns -1 and sets errno accordingly.
 */
int putsFdk(char *txt, int fd)
{
	int a = 0;

	if (!txt)
		return (0);
	while (*txt)
	{
		a += putFd(*txt++, fd);
	}
	return (a);
}
