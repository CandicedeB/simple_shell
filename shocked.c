#include "shell.h"

/**
 * isintact - checks if the shell is in interactive mode
 * @info: pointer to the info_t struct
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */

int isintact(info_t *info)
{
	/* Check if STDIN is a terminal and if the readFd is <= 2 */
	return (isatty(STDIN_FILENO) && info->readFd <= 2);
}
