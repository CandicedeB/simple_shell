#include "shell.h"

/**
 * Display - prints the current environment
 * @data: Structure parameter
 * Return: Always 0
 */
int printMyEnv(info_t *data)
{
	print_list_str(data->env);
	return (0);
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

	while (list)
	{
		q = starts_with(list->txt, name);
		if (q && *q)
			return (q);
		list = list->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a fresh environment variable,
 *             or modify an existing one
 * @data: Structure parameter
 *  Return: Always 0
 */
int _mysetenv(info_t *data)
{
	if (data->argc != 3)
	{
		eputin("Incorrect number of arguements\n");
		return (1);
	}
	if (fixEnv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *data)
{
	int a;

	if (data->argc == 1)
	{
		eputin("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= data->argc; a++)
		_unsetenv(data, data->argv[a]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *data)
{
	list_t *list = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&list, environ[a], 0);
	data->env = list;
	return (0);
}
