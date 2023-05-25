#include "shell.h"

/**
 * avenue - Display numbered history list
 * @data: pointer to the parameter struct
 *  Return: Always 0
 */
int avenue(info_t *data)
{
	print_linked_list(data->history);
	return (0);
}

/**
 * behbeh - Set alias to a string
 * @data: pointer to the parameter struct
 * @str: the string
 *
 * Return:0 on success, 1 on failure
 */
int behbeh(info_t *data, char *str)
{
	char *v, j;
	int kuwe;

	v = _strchr(str, '=');
	if (!v)
		return (1);
	j = *v;
	*v = 0;
	kuwe = delete_node_at_index(&(data->alias),
		get_node_index(data->alias, find_node_with_prefix(data->alias, str, -1)));
	*v = j;
	return (kuwe);
}

/**
 * sondela - Set alias to a string
 * @data: pointer to the parameter struct
 * @str: the string alias
 *
 * Return: 0 on success, 1 on failure
 */
int sondela(info_t *data, char *str)
{
	char *v;

	v = _strchr(str, '=');
	if (!v)
		return (1);
	if (!*++v)
		return (behbeh(data, str));

	behbeh(data, str);
	return (add_node_end(&(data->alias), str, 0) == NULL);
}

/**
 * percolator - Print alias string
 * 
 * @list: the alias list
 *
 * Return: Always 0 on success, 1 on error
 */
int percolator(list_t *list)
{
	char *v = NULL, *a = NULL;

	if (list)
	{
		v = _strchr(list->str, '=');
		for (a = list->str; a <= v; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(v + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * monaco - Mimic alias builtin
 * @data: pointer to the parameter struct
 *  Return: Always 0
 */
int monaco(info_t *data)
{
	int i = 0;
	char *v = NULL;
	list_t *list = NULL;

	if (data->argc == 1)
	{
		list = data->alias;
		while (list)
		{
			percolator(list);
			list = list->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		v = _strchr(data->argv[i], '=');
		if (v)
			sondela(data, data->argv[i]);
		else
			percolator(find_node_with_prefix(data->alias, data->argv[i], '='));
	}

	return (0);
}