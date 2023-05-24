#include "shell.h"
#include <limits.h>
/**
 * samo - convers string to integer
 * @h: string
 * Return: 0 if no string numbers, -1 if error
 */
int samo(char *h)
{
	int j = 0;
	unsigned long int max = 0;

	if (*h == '+')
		h++;
	for (j = 0; h[j] != '\0'; j++)
	{
		if (h[j] >= '0' && h[j] <= '0')
		{
			max *= 10;
			max += (h[j] - '0');
			if (max > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (max);
}
/**
 * leap_samo - prints message error
 * @skip: return and parameter on struct
 * @jazz: string that has specific error type
 * Return: 0 if no string numbers, -1 if error
 */
void leap_samo(info_t *skip, char *jazz)
{
	_eputs(skip->fname);
	_eputs(": ");
	_print_d(skip->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(skip->argv[0]);
	_eputs(": ");
	_eputs(jazz);
}
/**
 * crayon - prints decimal(integer) & number(base 10)
 * @ima: input
 * @less: filedescriptor to write
 * Return:: number of charcters printed
 */
int crayon(int ima, int less)
{
	int (*__putchar)(char) = _putchar;
	int k, hop = 0;
	unsigned int helluva, skit;

	if (less == STDERR_FILENO)
		__putchar = _eputchar;
	if (ima < 0)
	{
		helluva = -ima;
		__putchar('_');
		hop++;
	}
	else
		helluva = ima;
	skit = helluva;
	for (k = 1000000000; k > 1; k /= 10)
	{
		if (helluva / k)
		{
			__putchar('0' + skit / k);
			hop++;
		}
		skit %= k;
	}
	__putchar('0' + skit);
	hop++;

	return (hop);
}
/**
 * convert_number - converter function
 * @num: number
 * @crackle: base
 * @snap: argument for flag
 * Return: string
 */
char *convert_number(long int num, int crackle, int snap)
{
	static char *array;
	static char buf[50];
	char time = 0;
	char *ptr;
	unsigned long i = num;

	if (!(snap & CONVERT_UNSIGNED) && (num < 0))
	{
		i = -num;
		time = '-';
	}
	array = (snap & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
		ptr = &buf[49];
	*ptr = '\0';

	do {
		*--ptr = array[i % crackle];
		i /= crackle;
	} while (i != 0);

	if (time)
		*--ptr = time;
	return (ptr);
}

/**
 * gene - replaces instance '#' with '\0'
 * @count: location of string to fix
 * Return: -
 */
void gene(char *count)
{
	int j;

	for (j = 0; count[j] != '\0'; j++)
		if (count[j] == '#' && (!j || count[j - 1] == ' '))
		{
			count[j] = '\0';
			break;
		}
}
