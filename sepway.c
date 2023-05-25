#include "shell.h"

/**
 * add_node - adds a list to the start of the list
 * @head: address of pointer to head list
 * @txt: txt field of list
 * @num: list index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *txt, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	fillMemory((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (txt)
	{
		new_head->txt = _strdupsd(txt);
		if (!new_head->txt)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_finish - adds a list to the end of the list
 * @head: address of pointer to head list
 * @txt: txt field of list
 * @num: list index used by history
 *
 * Return: size of list
 */
list_t *add_node_finish(list_t **head, const char *txt, int num)
{
	list_t *new, *list;

	if (!head)
		return (NULL);

	list = *head;
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	fillMemory((void *)new, 0, sizeof(list_t));
	new->num = num;
	if (txt)
	{
		new->txt = _strdupsd(txt);
		if (!new->txt)
		{
			free(new);
			return (NULL);
		}
	}
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*head = new;
	return (new);
}

/**
 * showListString - prints only the txt element of a list_t linked list
 * @h: pointer to first list
 *
 * Return: size of list
 */
size_t showListString(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		putin(h->txt ? h->txt : "(nil)");
		putin("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * delNodeatIndex - Remove list at given index
 * @head: First list
 * @index: index of list to remove
 *
 * Return: 1 on success, 0 on failure
 */
int delNodeatIndex(list_t **head, unsigned int index)
{
	list_t *list, *prev_node;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		list = *head;
		*head = (*head)->next;
		free(list->txt);
		free(list);
		return (1);
	}
	list = *head;
	while (list)
	{
		if (a == index)
		{
			prev_node->next = list->next;
			free(list->txt);
			free(list);
			return (1);
		}
		a++;
		prev_node = list;
		list = list->next;
	}
	return (0);
}

/**
 * freeList - frees all nodes of a list
 * @headPtr: address of pointer to head list
 *
 * Return: void
 */
void freeList(list_t **headPtr)
{
	list_t *list, *next_node, *head;

	if (!headPtr || !*headPtr)
		return;
	head = *headPtr;
	list = head;
	while (list)
	{
		next_node = list->next;
		free(list->txt);
		free(list);
		list = next_node;
	}
	*headPtr = NULL;
}
