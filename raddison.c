#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = list_to_strings(data->env);
		data->env_changed = 0;
	}

	return (data->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *data, char *var)
{
	list_t *list = data->env;
	size_t a = 0;
	char *q;

	if (!list || !var)
		return (0);

	while (list)
	{
		q = starts_with(list->txt, var);
		if (q && *q == '=')
		{
			data->env_changed = delete_node_at_index(&(data->env), a);
			a = 0;
			list = data->env;
			continue;
		}
		list = list->next;
		a++;
	}
	return (data->env_changed);
}

/**
 * fixEnv - Initialize a fresh environment variable,
 *             or modify an existing one
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int fixEnv(info_t *data, char *var, char *value)
{
	char *buffed = NULL;
	list_t *list;
	char *q;

	if (!var || !value)
		return (0);

	buffed = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffed)
		return (1);
	copyString (buffed, var);
	_strcat(buffed, "=");
	_strcat(buffed, value);
	list = data->env;
	while (list)
	{
		q = starts_with(list->txt, var);
		if (q && *q == '=')
		{
			free(list->txt);
			list->txt = buffed;
			data->env_changed = 1;
			return (0);
		}
		list = list->next;
	}
	add_node_end(&(data->env), buffed, 0);
	free(buffed);
	data->env_changed = 1;
	return (0);
}
