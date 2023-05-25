#include "shell.h"

/**
 * displayHistory - displays the history list, 
 * @data: Parameter struct
 *  Return: Always 0
 */
int displayHistory(info_t *data)
{
	print_list(data->history);
	return (0);
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

	q = strChr(txt, '=');
	if (!q)
		return (1);
	c = *q;
	*q = 0;
	ret = delete_node_at_index(&(data->alias),
		get_node_index(data->alias, node_begins(data->alias, txt, -1)));
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

	q = strChr(txt, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unsetAlias(data, txt));

	unsetAlias(data, txt);
	return (add_node_end(&(data->alias), txt, 0) == NULL);
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
		for (a = list->txt; a <= q; a++)
			_putchar(*a);
		_putchar('\'');
		putin(q + 1);
		putin("'\n");
		return (0);
	}
	return (1);
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

	if (data->argc == 1)
	{
		list = data->alias;
		while (list)
		{
			printAlias(list);
			list = list->next;
		}
		return (0);
	}
	for (a = 1; data->argv[a]; a++)
	{
		q = strChr(data->argv[a], '=');
		if (q)
			setAlias(data, data->argv[a]);
		else
			printAlias(node_begins(data->alias, data->argv[a], '='));
	}

	return (0);
}
