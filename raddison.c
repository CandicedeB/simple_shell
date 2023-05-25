#include "shell.h"

/**
 * getEnviron - obtains a copy of the string array 'environ'
 * @data: Structure with potential arguments. Constant function prototype.
 * Return: Always 0
 */
char **getEnviron(info_t *data)
{
	/* Make the environment change flag, environment variable data is not null */
	if (!data->environ || data->env_changed)
	{
		/* Transform the list of environment variables into a string array */
		data->environ = list_to_strings(data->env);
		/* Setting the environment change flag back */
		data->env_changed = 0;
	}
	/* Give back the array of modified environment variables */
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
	/* Set a local variable to contain the list of environment variables */
	list_t *list = data->env;
	/* tracking variable for the node's current index in the list */
	size_t a = 0;
	/* Pointer used to record the outcome of determining */
	/* whether a string starts with a specific prefix */
	char *q;
	/* Verify if variable name or environment variable list contains null value */
	if (!list || !var)
		return (0);

	while (list) /* through the list repeatedly */
	{
		/* Verify if provided variable name appears in text of current list node */
		q = beginWith(list->txt, var);
		/* Verify that the variable name exactly matches and ends with "=." */
		if (q && *q == '=')
		{
			/* environment variable list should not contain node at current index */
			data->env_changed = delNodeatIndex(&(data->env), a);
			a = 0;
			/* Add the changed list to the local list variable */
			list = data->env;
			continue;
		}
		list = list->next;
		a++;
	}
	/* Give the environment change flag's value back */
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
	/* Iteration pointer for the list of environment variables */
	list_t *list;
	/* Pointer used to record outcome of determining whether */
	/* string starts with  specific prefix */
	char *q;

	if (!var || !value)
		return (0);

	buffed = malloc(stringLen(var) + stringLen(value) + 2);
	if (!buffed)
		return (1);
	copyString(buffed, var); /* Add variable name to string after concatenation */
	strConcat(buffed, "=");
	strConcat(buffed, value);
	/* Set a local variable to contain the list of environment variables */
	list = data->env;
	while (list)
	{
		/* Verify if provided variable name appears in text of current list node */
		q = beginWith(list->txt, var);
		if (q && *q == '=')
		{
			free(list->txt);
			/* Add the string's concatenation to the node's text */
			list->txt = buffed;
			data->env_changed = 1;
			return (0);
		} /* change to following node in list */
		list = list->next;
	}
	add_node_finish(&(data->env), buffed, 0);
	free(buffed);
	/* Change the environment's flag to show that anything has changed */
	data->env_changed = 1;
	return (0);
}
