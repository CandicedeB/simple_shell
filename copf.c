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
	/* Examine characters at buffed[b] & buffed[b + 1] to see if they are '|' */
	if (buffed[b] == '|' && buffed[b + 1] == '|')
	{
		buffed[b] = 0; /* Replace buffed[b] with null */
		b++;
		data->cmdBufType = CMD_OR; /* Set cmdBufType attribute of data to CMD_OR */
	}
	else if (buffed[b] == '&' && buffed[b + 1] == '&')
	{
		buffed[b] = 0;
		b++; /* Increment b */
		data->cmdBufType = CMD_AND;
	}
	else if (buffed[b] == ';') /* found end of this command */
	{
		buffed[b] = 0; /* replace semicolon with null */
		data->cmdBufType = CMD_CHAIN;
	}
	else
		return (0);
	*q = b; /* Update the value pointed to by q with b */
	return (1);
}

/**
 * valCha - checks if we should continue chaining based on the last word
 * @data: the parameter struct
 * @buffed: the char fender
 * @q: address of current position in buffed
 * @a: starting position in buffed
 * @length: length of buffed
 *
 * Return: Void
 */
void valCha(info_t *data, char *buffed, size_t *q, size_t a, size_t length)
{
	size_t b = *q;

	if (data->cmdBufType == CMD_AND) /* Check if cmdBufType is CMD_AND */
	{
		if (data->worth) /* make sure worth is non-zero */
		{
			buffed[a] = 0; /* Replace buffed[a] with null */
			b = length; /* Set b to value of length */
		}
	}
	if (data->cmdBufType == CMD_OR) /* make sure cmdBufType is CMD_OR */
	{
		if (!data->worth) /* check worth is non-zero */
		{
			buffed[a] = 0;
			b = length;
		}
	}

	*q = b; /* Update the value that q has referenced with b */
}

/**
 * substituteAlias  - change aliases in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int substituteAlias(info_t *data)
{
	int a;
	list_t *list;
	char *q;

	for (a = 0; a < 10; a++) /* Loop from 0 to 9 */
	{
		list = node_begins(data->alias, data->argv[0], '=');
		if (!list) /* Check if list is empty */
			return (0);
		free(data->argv[0]); /* Free memory allocated for data->argv[0] */
		q = strChr(list->txt, '='); /* Find the first occurrence of '=' */
		/* in list->txt and assign its address to q */
		if (!q)
			return (0);
		q = _strdupsd(q + 1); /* Duplicate string starting from q+1 & assign to q */
		if (!q)
			return (0);
		data->argv[0] = q; /* Update data->argv[0] with the new value in q */
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
	/* Loop through data->argv elements until the null element is encountered */
	for (a = 0; data->argv[a]; a++)
	{
		/* check if element doesn't start with '$' or is an empty string */
		if (data->argv[a][0] != '$' || !data->argv[a][1])
			continue; /* Ahead to the following iteration */

		if (!_strcmps(data->argv[a], "$?")) /* Check if the element is "$?" */
		{
			substituteString(&(data->argv[a]),
				_strdupsd(changeNum(data->worth, 10, 0)));
			continue;
		}
		if (!_strcmps(data->argv[a], "$$"))
		{
			substituteString(&(data->argv[a]),
				_strdupsd(changeNum(getpid(), 10, 0)));
			continue;
		}
		list = node_begins(data->env, &data->argv[a][1], '=');
		if (list) /* Check if a matching node is found */
		{
			substituteString(&(data->argv[a]),
				_strdupsd(strChr(list->txt, '=') + 1));
			continue;
		} /* Substitute the element with an empty string */
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
	free(*dry); /* Free the memory pointed to by the pointer dry */
	*dry = fresh; /* fresh value should be added to the value pointed to by dry */
	return (1);
}
