#include "shell.h"

/**
 * isChainDelim - checks if the character in the buffer is a chain delimiter
 * @data: the parameter struct
 * @buffed: the char fender
 * @q: address of current position in buffed
 *
 * Return: 1 if it is a chain delimiter, 0 otherwise
 */
int isChainDelim(info_t *data, char *buffed, size_t *q)
{
	size_t b = *q;

	if (buffed[b] == '|' && buffed[b + 1] == '|')
	{
		buffed[b] = 0;
		b++;
		data->cmdBufType = CMD_OR;
	}
	else if (buffed[b] == '&' && buffed[b + 1] == '&')
	{
		buffed[b] = 0;
		b++;
		data->cmdBufType = CMD_AND;
	}
	else if (buffed[b] == ';') /* found end of this command */
	{
		buffed[b] = 0; /* replace semicolon with null */
		data->cmdBufType = CMD_CHAIN;
	}
	else
		return (0);
	*q = b;
	return (1);
}

/**
 * validateChain - checks if we should continue chaining based on the last word
 * @data: the parameter struct
 * @buffed: the char fender
 * @q: address of current position in buffed
 * @a: starting position in buffed
 * @length: length of buffed
 *
 * Return: Void
 */
void validateChain(info_t *data, char *buffed, size_t *q, size_t a, size_t length)
{
	size_t b = *q;

	if (data->cmdBufType == CMD_AND)
	{
		if (data->worth)
		{
			buffed[a] = 0;
			b = length;
		}
	}
	if (data->cmdBufType == CMD_OR)
	{
		if (!data->worth)
		{
			buffed[a] = 0;
			b = length;
		}
	}

	*q = b;
}

/**
 * substituteAlias  - change aliases in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int substituteAlias (info_t *data)
{
	int a;
	list_t *list;
	char *q;

	for (a = 0; a < 10; a++)
	{
		list = node_begins(data->alias, data->argv[0], '=');
		if (!list)
			return (0);
		free(data->argv[0]);
		q = strChr(list->txt, '=');
		if (!q)
			return (0);
		q = _strdupsd(q + 1);
		if (!q)
			return (0);
		data->argv[0] = q;
	}
	return (1);
}

/**
 * substituteVar - performs variable substitution in the tokenized string
 * @data: the parameter struct
 * Return: 1 if variables were successfully replaced, 0 otherwise
 */
int substituteVar(info_t *data)
{
	int a = 0;
	list_t *list;

	for (a = 0; data->argv[a]; a++)
	{
		if (data->argv[a][0] != '$' || !data->argv[a][1])
			continue;

		if (!_strcmps(data->argv[a], "$?"))
		{
			substituteString(&(data->argv[a]),
				_strdupsd(chnageNum(data->worth, 10, 0)));
			continue;
		}
		if (!_strcmps(data->argv[a], "$$"))
		{
			substituteString(&(data->argv[a]),
				_strdupsd(chnageNum(getpid(), 10, 0)));
			continue;
		}
		list = node_begins(data->env, &data->argv[a][1], '=');
		if (list)
		{
			substituteString(&(data->argv[a]),
				_strdupsd(strChr(list->txt, '=') + 1));
			continue;
		}
		substituteString(&data->argv[a], _strdupsd(""));

	}
	return (0);
}

/**
 * substituteString - replaces a specific string with a fresh string
 * @dry: address place of older string
 * @fresh: newly formed string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int substituteString(char **dry, char *fresh)
{
	free(*dry);
	*dry = fresh;
	return (1);
}
