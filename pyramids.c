#include "shell.h"

/**
 * printMyEnv - prints the current environment
 * @data: Structure parameter
 * Return: Always 0
 */
int printMyEnv(info_t *data)
{
	showListString(data->env); /* Display the contents of the "env" list */
	return (0); /* Return 0 to indicate successful execution */
}

/**
 * findEnv - gets the value of an environ variable
 * @data: Structure parameter
 * @name: env var name
 *
 * Return: the value
 */
char *findEnv(info_t *data, const char *name)
{
	list_t *list = data->env;
	char *q;

	while (list) /* Iterate through the list until it reaches the end (NULL) */
	{
		q = beginWith(list->txt, name);
		if (q && *q) /* "q" is not NULL & value points to is not null terminator */
			return (q); /* Return the value of "q" indicating a match */
		list = list->next;
	}
	return (NULL);
}

/**
 * setEnvVar - Initialize a fresh environment variable,
 *             or modify an existing one
 * @data: Structure parameter
 *  Return: Always 0
 */
int setEnvVar(info_t *data)
{
	if (data->argc != 3)
	{
		/* Print an error message indicating incorrect number of arguments */
		eputin("Incorrect number of arguements\n");
		return (1); /* Return 1 to indicate an error condition */
	}
	if (fixEnv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * removeEnvVar - Remove the env variable with shell
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int removeEnvVar(info_t *data)
{
	int a;

	if (data->argc == 1) /* Check argument count stored in "data" is equal to 1 */
	{
		eputin("Too few arguements.\n");
		return (1); /* Return 1 to indicate an error condition */
	}
	for (a = 1; a <= data->argc; a++)
		/* Call the "remEnv()" function with the current argument from "data" */
		remEnv(data, data->argv[a]);

	return (0);
}

/**
 * filEnvList - populates env linked list
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int filEnvList(info_t *data)
{
	list_t *list = NULL;
	size_t a;
	/* Iterate through "environ" array until a null terminator is encountered */
	for (a = 0; environ[a]; a++)
		add_node_finish(&list, environ[a], 0);
	data->env = list; /* Assign created "list" to "env" field in "data" struc */
	return (0);
}
