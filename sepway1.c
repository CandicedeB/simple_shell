#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first list
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - returns an array of strings of the list->txt
 * @head: pointer to first list
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *list = head;
	size_t a = list_len(head), b;
	char **strs;
	char *txt;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; list; list = list->next, a++)
	{
		txt = malloc(stringLen(list->txt) + 1);
		if (!txt)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		txt = copyString(txt, list->txt);
		strs[a] = txt;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * displayList - prints all elements of a list_t linked list
 * @h: pointer to first list
 *
 * Return: size of list
 */
size_t displayList(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		putin(changeNum(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		putin(h->txt ? h->txt : "(nil)");
		putin("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * node_begins - returns list whose string starts with prefix
 * @list: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match list or null
 */
list_t *node_begins(list_t *list, char *prefix, char c)
{
	char *q = NULL;

	while (list)
	{
		q = beginWith(list->txt, prefix);
		if (q && ((c == -1) || (*q == c)))
			return (list);
		list = list->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a list
 * @head: pointer to list head
 * @list: pointer to the list
 *
 * Return: index of list or -1
 */
ssize_t get_node_index(list_t *head, list_t *list)
{
	size_t a = 0;

	while (head)
	{
		if (head == list)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}
