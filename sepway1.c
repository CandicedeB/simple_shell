#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first list
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	/* Loop while 'h' is not NULL (assuming 'h' is pointer to linked list node) */
	size_t a = 0;

	while (h)
	{
		h = h->next; /* Move to the next node in the linked list */
		a++; /* Increase the number */
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
	if (!strs) /* memory allocation fails, return NULL */
		return (NULL);
	for (a = 0; list; list = list->next, a++) /* Loop through the linked list */
	{
		txt = malloc(stringLen(list->txt) + 1);
		if (!txt)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		txt = copyString(txt, list->txt); /* Copy content 'list->txt' to 'txt' */
		strs[a] = txt; /* Assign 'txt' to the current position in 'strs' array */
	}
	strs[a] = NULL; /* Set the last element of 'strs' array to NULL */
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
		putin(changeNum(h->num, 10, 0)); /* Print modified value of 'h->num' */
		_putchar(':'); /* Print a colon character */
		_putchar(' '); /* Print a space character */
		putin(h->txt ? h->txt : "(nil)");
		putin("\n"); /* Print a newline character */
		h = h->next; /* Move to the next node in the linked list */
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
		/* 'list->txt' begins with 'prefix' and assign the result to 'q' */
		q = beginWith(list->txt, prefix);
		if (q && ((c == -1) || (*q == c)))
			/* 'q' is not NULL & either 'c' is -1 or first character 'q' matches 'c' */
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
		if (head == list) /* 'head' is equal to 'list', return current count 'a' */
			return (a);
		head = head->next;
		a++;
	}
	return (-1); /* Return -1 if loop finishes without finding 'list' */
}
