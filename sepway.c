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
	new_head = malloc(sizeof(list_t)); /* assign memory for new node */
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
	new_head->next = *head; /* Set new nodes 'next' refr to current head */
	*head = new_head; /* Affix the new node to the head pointer as necessary */
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

	if (!head) /* amke sure head pointer is NULL */
		return (NULL);

	list = *head; /* list should be given head pointers value */
	new = malloc(sizeof(list_t)); /* assign memory for new node */
	if (!new)
		return (NULL);
	fillMemory((void *)new, 0, sizeof(list_t));
	new->num = num; /* new node's "num" value should be set */
	if (txt)
	{
		/* 'txt' should be duplicated and assigned to 'new->txt' */
		new->txt = _strdupsd(txt);
		if (!new->txt)
		{
			free(new);
			return (NULL);
		}
	}
	if (list) /* make sure list isn't empty */
	{
		while (list->next) /* Navigate to the list's conclusion */
			list = list->next;
		list->next = new;
	}
	else
		*head = new; /* head pointer should be updated to new node, list is empty */
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
	/* Set the initial value of the counter 'a' to 0 */
	while (h)
	{
		/* cycle through the list until 'h' is replaced with NULL */
		/* If H->TXT is not NULL, use "(nil)" to invoke the "putin" function */
		putin(h->txt ? h->txt : "(nil)");
		putin("\n"); /* Make a newline character */
		h = h->next;
		a++; /* Adjust the counter 'a' */
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

	if (!index) /* make sure index is 0 */
	{
		/* Delete the list's initial node if the index is 0 */
		/* 'list' should be given the head pointer's value */
		list = *head;
		*head = (*head)->next;
		free(list->txt);
		free(list);
		return (1); /* Return 1 to signify that the removal was successful */
	}
	list = *head;
	while (list)
	{
		if (a == index) /* Verify that index 'a' matches the requested index */
		{
			/* Delete the node if the index matches */
			prev_node->next = list->next;
			free(list->txt);
			free(list);
			return (1);
		}
		a++;
		prev_node = list; /* The 'prev_node' pointer should */
		/* be updated to the current node */
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
	/* Verify whether the list is empty or the headPtr contains NULL */
	if (!headPtr || !*headPtr)
		return;
	head = *headPtr;
	list = head;
	while (list) /* go over the list and release each node's memory */
	{
		/* After releasing the current node, save the pointer for the */
		/* following node to prevent losing it */
		next_node = list->next;
		free(list->txt);
		free(list);
		list = next_node;
	} /* set head pointer to NULL */
	*headPtr = NULL;
}
