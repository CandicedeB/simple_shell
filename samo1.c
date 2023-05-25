#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *s)
{
	int a = 0;
	unsigned long int answer = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			answer *= 10;
			answer += (s[a] - '0');
			if (answer > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (answer);
}

/**
 * display_err - prints an error message
 * @data: the parameter & return data struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void display_err(info_t *data, char *estr)
{
	eputin(data->fname);
	eputin(": ");
	printDD(data->line_count, STDERR_FILENO);
	eputin(": ");
	eputin(data->argv[0]);
	eputin(": ");
	eputin(estr);
}

/**
 * printDD - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int printDD(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = eputword;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + current / a);
			count++;
		}
		current %= a;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * chnageNum - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *chnageNum(long int num, int base, int flags)
{
	static char *array;
	static char fender[50];
	char tive = 0;
	char *word;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		tive = '-';

	}
	array = flags & CONVERT_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	word = &fender[49];
	*word = '\0';

	do	{
		*--word = array[n % base];
		n /= base;
	} while (n != 0);

	if (tive)
		*--word = tive;
	return (word);
}

/**
 * vanishComments - function replaces first instance of '#' with '\0'
 * @buffed: address of the string to modify
 *
 * Return: Always 0;
 */
void vanishComments(char *buffed)
{
	int a;

	for (a = 0; buffed[a] != '\0'; a++)
		if (buffed[a] == '#' && (!a || buffed[a - 1] == ' '))
		{
			buffed[a] = '\0';
			break;
		}
}
