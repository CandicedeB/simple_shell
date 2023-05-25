#include "shell.h"

/**
 * copyString  - copies a string
 * @dest: the place
 * @place: the source
 *
 * Return: pointer to end point
 */
char *copyString(char *dest, char *place)
{
	int a = 0;
	/* Check for exceptional circumstances, such as when the destination and */
	/* the location are the same or when the location is NULL */
	if (dest == place || place == 0)
		return (dest);
	/* Copying characters from one place to another until */
	/* the null terminator is reached */
	while (place[a])
	{
		dest[a] = place[a];
		a++;
	}
	dest[a] = 0; /* the target string should have a null terminator added */
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
	/* make sure input string is NULL */
	if (txt == NULL)
		return (NULL);
	/* Determine the input string's length */
	while (*txt++)
		length++;
	/* Memory should be set aside for the repeated string */
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	/* Reverse-transfer the input string's characters to the replica string */
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

	if (!txt) /* make sure input string is NULL */
		return;
	while (txt[a] != '\0')
	{
		_putchar(txt[a]); /* character needs to be printed */
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
	static char buffed[WRITE_BUFFER];
	/* Verify the character's flushing behavior or whether the buffer is full */
	if (c == BUFFER_FLUSHER || a >= WRITE_BUFFER)
	{
		write(1, buffed, a); /* To standard output, send characters in the buffer */
		a = 0; /* rearrange buffer index */
	}
	/* The character should not be a buffer flusher, so check */
	if (c != BUFFER_FLUSHER)
		buffed[a++] = c; /* Fill the buffer with the character */
	return (1);
}
