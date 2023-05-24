#include "shell.h"
/**
 * _eputs - prints input to string
 * @blop: string to be printed
 *
 * Return: 0
 */
void _eputs(char *blop)
{
	int j = 0;

	if (!blop) /* checks if string is empty */
		return; /* return instantly, if empty or NULL */
	while (blop[j] != '\0') /* Iterate until NULL string is reached */
	{
		_eputchar(blop[j]); /* calls function to print charcter of string */
		j++; /* move to following charcter */
	}
}
/**
 * _eputchar - writes character n to STDERR
 * @n: character to print
 *
 * Return: Success 1, Error -1
 */
int _eputchar(char n)
{
	static int k; /* keeps track of buffer index */
	static char buf[BUFFER]; /* stores charcters */

	if (n == BUFFER_FLUSHER || k >= BUFFER)
	{
		write(2, buf, k); /* writes content to STDERR and resets index */
		k = 0;
	}
	if (n != BUFFER_FLUSHER)
		buf[k++] = n; /* stores charcter in buffer */
	return (1);
}
