#include "shell.h"

/**
 * getEnviron - obtains a copy of the string array 'environ'
 * @data: Structure with potential arguments. Constant function prototype.
 * Return: Always 0
 */
char **getEnviron(info_t *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = list_to_strings(data->env);
		data->env_changed = 0;
	}

	return (data->environ);
}

/**
 * remEnv - Deletes an environment variable
 * @data:  Structure with potential arguments. Constant function prototype.
 * @var: the environment variable to be deleted
 * Return: 1 if the variable is successfully removed, 0 otherwise
 */
int remEnv(info_t *data, char *var)
{
	list_t *list = data->env;
	size_t a = 0;
	char *q;

	if (!list || !var)
		return (0);

	while (list)
	{
		q = beginWith(list->txt, var);
		if (q && *q == '=')
		{
			data->env_changed = delNodeatIndex(&(data->env), a);
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
 * fixEnv - Initializes a new environment variable or modifies an existing one
 * @data: Structure with potential arguments. Constant function prototype.
 * @var: the environment variable to initialize or modify
 * @value: the value to assign to the environment variable
 *  Return: Always 0
 */
int fixEnv(info_t *data, char *var, char *value)
{
	char *buffed = NULL;
	list_t *list;
	char *q;

	if (!var || !value)
		return (0);

	buffed = malloc(stringLen(var) + stringLen(value) + 2);
	if (!buffed)
		return (1);
	copyString(buffed, var);
	strConcat(buffed, "=");
	strConcat(buffed, value);
	list = data->env;
	while (list)
	{
		q = beginWith(list->txt, var);
		if (q && *q == '=')
		{
			free(list->txt);
			list->txt = buffed;
			data->env_changed = 1;
			return (0);
		}
		list = list->next;
	}
	add_node_finish(&(data->env), buffed, 0);
	free(buffed);
	data->env_changed = 1;
	return (0);
}
