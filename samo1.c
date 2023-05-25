#include "shell.h"

/**
 * errAtoi - Convert a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int errAtoi(char *s)
{
	int a = 0;
	unsigned long int answer = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9') /* makes sure character is digit */
		{
			answer *= 10;
			answer += (s[a] - '0'); /* changes character to linked number value */
			if (answer > INT_MAX)
				/* determines whether accumulated value is more than int's maximum limit */
				return (-1); /* Return -1 to indicates overflow */
		}
		else
			return (-1);
	}
	return (answer);
}

/**
 * display_err - Output an error message
 * @data: the  parameter and return data struct
 * @estr: string containing the specified error type
 * Return: 0 on success, -1 on error
 */
void display_err(info_t *data, char *estr)
{
	eputin(data->fname); /* prints the file name found in data->fname */
	eputin(": "); /* a colon and a space are printed */
	printDD(data->line_count, STDERR_FILENO); /* outputs to standard error the */
	/* line count that is recorded in data->line_count */
	eputin(": ");
	eputin(data->argv[0]); /* displays the first argument from data->argv */
	eputin(": ");
	eputin(estr); /* returns a string that was supplied as the estr argument */
}

/**
 * printDD - Displays a decimal (integer) number in base 10
 * @input: the number to be displayed
 * @fd: the file descriptor to write the output to
 *
 * Return: number of characters printed
 */
int printDD(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a, count = 0; /* 'a' & 'count' declared with starting values of 0 */
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar = eputword;
	if (input < 0) /* determines whether the value of 'input' is smaller than 0 */
	{
		_abs_ = -input;
		__putchar('-');
		count++; /* Adds 1 to the 'count' variable */
	}
	else
		_abs_ = input; /* gives variable "_abs_" value of the argument "input" */
	curr = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a) /* determines whether '_abs_' divided by 'a' is not zero */
		{
			__putchar('0' + curr / a);
			count++;
		}
		curr %= a;
	}
	__putchar('0' + curr);
	count++;

	return (count);
}

/**
 * changeNum - Converts a number to a string representation
 * @num: number to be converted
 * @base: base for conversion
 * @flags: argument flags
 *
 * Return: string
 */
char *changeNum(long int num, int base, int flags)
{
	static char *array;
	static char fender[50];
	char tive = 0; /* char 'tive' variable was set to 0 */
	char *word; /* variable with char pointer 'word' */
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num; /* gives 'n' the negative of 'num' */
		tive = '-'; /* the letter "-" is added to the word "tive" */

	}
	array = flags & CONVERT_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	word = &fender[49];
	*word = '\0';

	do	{
		*--word = array[n % base];
		n /= base; /* divides 'n' by 'base' and returns the outcome to 'n' */
	} while (n != 0); /* Loops so long as 'n' is not equal to 0 */

	if (tive)
		*--word = tive;
	return (word);
}

/**
 * vanishComments - Replaces first instance of '#' with '\0'
 * @buffed: address of the string to be changed
 *
 * Return: Always 0;
 */
void vanishComments(char *buffed)
{
	int a; /* 'a', an integer variable, is declared */

	for (a = 0; buffed[a] != '\0'; a++)
		if (buffed[a] == '#' && (!a || buffed[a - 1] == ' '))
		{
			buffed[a] = '\0';
			break; /* Breaks out of the loop after removing the comment */
		}
}
