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
	fillMemory ((void *)new_head, 0, sizeof(list_t));
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
 * add_node_end - adds a list to the end of the list
 * @head: address of pointer to head list
 * @txt: txt field of list
 * @num: list index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *txt, int num)
{
	list_t *new_node, *list;

	if (!head)
		return (NULL);

	list = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	fillMemory ((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (txt)
	{
		new_node->txt = _strdupsd(txt);
		if (!new_node->txt)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the txt element of a list_t linked list
 * @h: pointer to first list
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
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
 * delete_node_at_index - deletes list at given index
 * @head: address of pointer to first list
 * @index: index of list to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
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
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head list
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *list, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	list = head;
	while (list)
	{
		next_node = list->next;
		free(list->txt);
		free(list);
		list = next_node;
	}
	*head_ptr = NULL;
}
