#include "shell.h"

/**
 * fjord - Returns environ string array copy 
 * @data: pointer to the parameter struct
 * Return: Always 0
 */
char **fjord(info_t *data)
{
	if (!data->environs || data->envChanged)
	{
		data->environs = convert_list_to_strings(data->env);
		data->envChanged = 0;
	}

	return (data->environs);
}

/**
 * dunia - Remove env variable
 * @data: pointer to the parameter struct
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int dunia(info_t *data, char *var)
{
	list_t *listly = data->env;
	size_t i = 0;
	char *p;

	if (!listly || !var)
		return (0);

	while (listly)
	{
		p = starts_with(listly->text, var);
		if (p && *p == '=')
		{
			data->envChanged = delete_node_at_index(&(data->env), i);
			i = 0;
			listly = data->env;
			continue;
		}
		listly = listly->next;
		i++;
	}
	return (data->envChanged);
}

/**
 * ottolenghi - Init/modify env variable
 * @data: pointer to the parameter struct
 * @var: the string env var property
 * @num: the string env var value
 *  Return: Always 0
 */
int ottolenghi(info_t *data, char *var, char *num)
{
	char *buf = NULL;
	list_t *listly;
	char *p;

	if (!var || !num)
		return (0);

	buf = malloc(_strlen(var) + _strlen(num) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, num);
	listly = data->env;
	while (listly)
	{
		p = starts_with(listly->text, var);
		if (p && *p == '=')
		{
			free(listly->text);
			listly->text = buf;
			data->envChanged = 1;
			return (0);
		}
		listly = listly->next;
	}
	add_node_end(&(data->env), buf, 0);
	free(buf);
	data->envChanged = 1;
	return (0);
}