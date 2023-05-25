#include "shell.h"

/**
 **fillMemory  - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *fillMemory(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}

/**
 * freeStringArray  - frees a string of strings
 * @pp: string of strings
 */
void freeStringArray(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * reallocateMemory - reallocates a block of memory
 * @word: pointer to previous malloc'ated block
 * @old: byte size of previous block
 * @new: byte size of fresh block
 *
 * Return: pointer to da ol'block nameen.
 */

void *reallocateMemory(void *word, unsigned int old, unsigned int new)
{
	char *q;

	if (!word)
		return (malloc(new));
	if (!new)
		return (free(word), NULL);
	if (new == old)
		return (word);

	q = malloc(new);
	if (!q)
		return (NULL);

	old = old < new ? old : new;
	while (old--)
		q[old] = ((char *)word)[old];
	free(word);
	return (q);
}