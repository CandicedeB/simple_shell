#include "shell.h"

/**
 * oxford_circus - Function to print out the current environment
 * @data: pointer to the parameter struct
 * Return: Always 0
 */
int oxford_circus(info_t *data)
{
	print_list_str(data->env);
	return (0);
}

/**
 * mndsgn - Get value of environ variable
 * @data: pointer to the parameter struct
 * @text: env var text
 *
 * Return: the value
 */
char *mndsgn(info_t *data, const char *text)
{
	list_t *list = data->env;
	char *p;

	while (list)
	{
		p = starts_with(list->text, text);
		if (p && *p)
			return (p);
		list = list->next;
	}
	return (NULL);
}

/**
 * sibali - Initialize or modify env variable
 * @data: pointer to the parameter struct
 *  Return: Always 0
 */
int sibali(info_t *data)
{
	if (data->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (ottolenghi(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * carluccio - Takes out an env variable
 * @data: pointer to the parameter struct
 *  Return: Always 0
 */
int carluccio(info_t *data)
{
	int i;

	if (data->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= data->argc; i++)
		dunia(data, data->argv[i]);

	return (0);
}

/**
 * coogie - Fills up env linked list
 * @data: pointer to the parameter struct
 * Return: Always 0
 */
int coogie(info_t *data)
{
	list_t *list = NULL;
	size_t i;

	for (i = 0; environs[i]; i++)
		add_node_end(&list, environs[i], 0);
	data->env = list;
	return (0);
}