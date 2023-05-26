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

	for (a = 0; a < n; a++) /* Loop from 0 to 'n-1' & assign value to 'a' */
		s[a] = b; /* Set value of 'b' to element at index 'a' in array 's' */
	return (s); /* Return the modified array 's' */
}

/**
 * freeStringArray  - frees a string of strings
 * @pp: string of strings
 */
void freeStringArray(char **pp)
{
	char **a = pp;

	if (!pp) /* 'pp' is a null pointer, exit the function */
		return;
	while (*pp) /* value pointed to by 'pp' is not null */
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

	if (!word) /* 'word' is a null pointer */
		return (malloc(new)); /* Allocate memory of size 'new' and return pointer */
	if (!new) /* 'new' is zero */
		return (free(word), NULL);
	if (new == old) /* 'new' is equal to 'old' */
		return (word); /* Return the original 'word' pointer without any changes */

	q = malloc(new); /* Allocate memory of size 'new' & assign pointer to 'q' */
	if (!q) /* 'q' is a null pointer (allocation failed) */
		return (NULL);

	old = old < new ? old : new; /* determine smaller size between 'old'&'new' */
	while (old--) /* Iterate 'old' number of times */
		q[old] = ((char *)word)[old]; /* Copy each character from 'word' to 'q' */
	free(word); /* Free memory pointed to by 'word' */
	return (q);
}
