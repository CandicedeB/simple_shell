#include "shell.h"

/**
 * displayHistory - displays the history list
 *  @data: Parameter struct
 *  Return: Always 0
 */
int displayHistory(info_t *data)
{
	displayList(data->history); /* Invoke a function to see the history list */
	return (0); /* If the execution was successful, return 0 */
}

/**
 * unsetAlias - sets an alias to string
 * @data: parameter struct
 * @txt: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unsetAlias(info_t *data, char *txt)
{
	char *q, c;
	int ret;
	/* Determine where the equal sign is located in the alias string */
	q = strChr(txt, '=');
	if (!q)
		return (1);
	c = *q; /* Save the character next to the equals sign */
	*q = 0; /* The alias name should be separated from the equal */
	/* sign by a null terminator */
	ret = delNodeatIndex(&(data->alias),
		get_node_index(data->alias, node_begins(data->alias, txt, -1)));
	/* Eliminate the alias node from the list of aliases */
	*q = c;
	return (ret);
}

/**
 * setAlias - assigns an alias to a string
 * @data: parameter struct
 * @txt: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int setAlias(info_t *data, char *txt)
{
	char *q;
	/* Determine where the equal sign is located in the alias string */
	q = strChr(txt, '=');
	if (!q)
		return (1);
	if (!*++q) /* Whenever a null terminator follows an equal sign */
		return (unsetAlias(data, txt)); /* Remove the alias */

	unsetAlias(data, txt); /* If an alias already exists, remove it */
	/* Return the outcome after adding the alias to the alias list */
	return (add_node_finish(&(data->alias), txt, 0) == NULL);
}

/**
 * printAlias - Display an alias string
 * @list: the alias list
 *
 * Return: Always 0 on success, 1 on error
 */
int printAlias(list_t *list)
{
	char *q = NULL, *a = NULL;

	if (list)
	{
		q = strChr(list->txt, '=');
		/* the alias name should appear before the equal sign */
		for (a = list->txt; a <= q; a++)
			_putchar(*a);
		_putchar('\''); /* signify beginning of the alias value, print a single quote */
		putin(q + 1); /* Print the value for the alias following the equal sign */
		putin("'\n"); /* finish the output from alias, print a newline character */
		return (0);
	}
	return (1); /* If the alias cannot be identified or printed, return 1 */
}

/**
 * mineAlias - mimics the alias builtin (man alias)
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int mineAlias(info_t *data)
{
	int a = 0;
	char *q = NULL;
	list_t *list = NULL;

	if (data->argc == 1) /* Verify that no arguments are given */
	{
		list = data->alias;
		while (list)
		{
			printAlias(list); /* Print the list of aliases, one by one */
			list = list->next;
		}
		return (0); /* If the execution was successful, return 0 */
	}
	/* Analyze each argument */
	for (a = 1; data->argv[a]; a++)
	{
		/* Verify the equal sign is present in the argument */
		q = strChr(data->argv[a], '=');
		if (q)
			setAlias(data, data->argv[a]); /* Change the alias */
		else
			/* Publish the unique alias */
			printAlias(node_begins(data->alias, data->argv[a], '='));
	}

	return (0);
}
