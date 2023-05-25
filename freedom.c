#include "shell.h"

/**
 * beFreed - frees a pointer and NULLs the address
 * @word: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */

int beFreed(void **word)
{
	if (word && *word)
	{
		free(*word);
		*word = NULL;
		return (1);
	}
	return (0);
}