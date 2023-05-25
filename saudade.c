#include "shell.h"

/**
 * cleanData - initializes info_t struct
 * @data: struct address
 */
void cleanData(info_t *data)
{
	/* Set the 'arg' member of 'data' to NULL */
	data->arg = NULL;
	/* Set the 'argv' member of 'data' to NULL */
	data->argv = NULL;
	/* Set the 'path' member of 'data' to NULL */
	data->path = NULL;
	/* Set the 'argc' member of 'data' to 0 */
	data->argc = 0;
}

/**
 * fixData - initializes info_t struct
 * @data: struct address
 * @av: argument vector
 */
void fixData(info_t *data, char **av)
{
	int a = 0;
	/* Set the 'fname' component of 'data' to the 'av's first element */
	data->fname = av[0];
	/* Verify that the 'arg' member of the 'data' is not NULL */
	if (data->arg)
	{
		/* arg divided into an array of strings using spaces & tabs as delimiters */
		data->argv = strSplit(data->arg, " \t");
		/* Check if 'argv' is still NULL after splitting 'arg' */
		if (!data->argv)
		{

			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdupsd(data->arg);
				data->argv[1] = NULL; /* Set the second element of 'argv' to NULL */
			}
		}
		for (a = 0; data->argv && data->argv[a]; a++)
			;
		data->argc = a;

		substituteAlias(data); /* Replace aliases where necessary */
		substituteVar(data); /* Substitute variables as necessary */
	}
}

/**
 * freeData - frees info_t struct fields
 * @data: struct address
 * @all: true if freeing all fields
 */
void freeData(info_t *data, int all)
{
	freeStringArray(data->argv);
	data->argv = NULL;
	data->path = NULL;
	/* Make sure the 'all' argument is true */
	if (all)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			freeList(&(data->env));
		if (data->history)
			freeList(&(data->history));
		if (data->alias)
			freeList(&(data->alias));
		freeStringArray(data->environ);
			data->environ = NULL;
		beFreed((void **)data->cmd_buf);
		/* Check if 'readingFd' member of 'data' is greater than 2 and */
		/* close the file descriptor */
		if (data->readingFd > 2)
			close(data->readingFd);
		_putchar(BUFFER_FLUSHER);
	}
}
