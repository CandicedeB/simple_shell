#include "shell.h"

/**
 * cleanData - initializes info_t struct
 * @data: struct address
 */
void cleanData(info_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
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

	data->fname = av[0];
	if (data->arg)
	{
		data->argv = strtow(data->arg, " \t");
		if (!data->argv)
		{

			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdupsd(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (a = 0; data->argv && data->argv[a]; a++)
			;
		data->argc = a;

		substituteAlias(data);
		substituteVar(data);
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
	if (all)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			free_list(&(data->env));
		if (data->history)
			free_list(&(data->history));
		if (data->alias)
			free_list(&(data->alias));
		freeStringArray(data->environ);
			data->environ = NULL;
		beFreed((void **)data->cmd_buf);
		if (data->readingFd > 2)
			close(data->readingFd);
		_putchar(BUFFER_FLUSHER);
	}
}
