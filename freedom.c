#include "shell.h"

/**
 * beFreed - frees a pointer and NULLs the address
 * @word: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */

int beFreed(void **word)
{
	if (word && *word) /* make sure pointer & memory points are correct */
	{
		free(*word); /* defragment memory that pointer is pointing to */
		*word = NULL;
		return (1); /* return to 1 will show success on freed memory */
	}
	return (0); /* return to 0 if pointer or memory in incorrect */
}
