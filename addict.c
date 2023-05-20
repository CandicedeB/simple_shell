#include "shell.h"


/**
 * add_node - Entry point
 * Description: Adds new node at the beginning of the list
 * @head: Pointer to the head of the list_t list
 * @text: String added to the list_t list
 * @len: Length used by list
 *
 * Return: the address of the new element, or NULL if it failed
 */

list_t *add_node(list_t **head, const char *text, int len)
{
	list_t *new;

	new = malloc(sizeof(list_t));
	if (!new)
	{
		return (NULL);
	}
	/* Duplicate the string */
	new->text = _strdup(text);
	if (new->text == NULL)
	{
		free(new);
		return (NULL);
	}
	/* Count the number of characters within square brackets */
	len = 0;
	while (text[len])
		len++;
	/* Set next pointer of new node to current head */
	new->next = *head;
	new->value = len;
	/* Set head to point to the new node */
	*head = new;

	return (new);
}

/**
 * add_node_end - Entry point
 * Description: Adds new node at the end of a list_t list
 * @head: Pointer to pointer to the head node of the list
 * @text: String stored in the new node
 * Return: Address of the new element, or NULL if it failed
 */

list_t *add_node_end(list_t **head, const char *text)
{
	list_t *new, *current;

	if (!head)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	/* Duplicate the string */
	new->text = _strdup(text);
	if (!new->text)
	{
		free(new);
		return (NULL);
	}
	/* Count the number of characters within square brackets */
	new->len = _strlen(text);
	new->next = NULL;
	/* If the list is empty, the new node becomes the head */
	if (!*head)
	{
		*head = new;
		return (new);
	}
	current = *head;
	/* Traverse the list until the last node is reached */
	while (current->next)
	{
		current = current->next;
	}
	/* Add the new node to the end of the list */
	current->next = new;
	return (new);
}

/**
 * print_list_str - Entry point
 * Description: Prints all the elements of list_t list
 * @h: Pointer to head of the list
 * Return: Number of nodes in list
 */

size_t print_list_str(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(h->text ? h->text : "(nil)");
		_puts("\n");
		count++;
		h = h->next;
	}

	return (count);
}

/**
 * delete_node_at_index - Entry point
 * Description: Deletes the node at index index of a list_t linked list.
 * @head: Pointer to pointer of first node in linked list
 * @index: Index of the node that should be deleted.
 *
 * Return: 1 if it succeeded, -1 if it failed
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *temp, *current;
	unsigned int i;
	/* Where i is the node */

	/* Checks if head is empty */
	if (!(*head))
		return (-1);
	if (index == 0)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
		return (1);
	}
	/* Checks node before it get removed */
	current = *head;
	for (i = 0; i < (index - 1); i++)
	{
		/* Checks if index is out of range */
		if (!current->next)
			return (-1);
		current = current->next;
	}
	/* Delete the node at index */
	temp = current->next;
	current->next = temp->next;
	free(temp);
	/* Success */
	return (1);
}

/**
 * free_list - Entry point
 * Description: Frees a linked list
 * @head: A pointer to the head of the list
 */

void free_list(list_t *head)
{
	list_t *current;

	while (head)
	{
		current = head->next;
		free(head->text);
		free(head);
		head = current;
	}
}

/**
 * list_len - Entry point
 * Description: Returns number of elements in linked list_t list
 * @h: Pointer to the head of the linked list
 * Return: Number of nodes in linked list
 */

size_t list_len(const list_t *h)
{
	size_t count_nodes = 0;

	while (h != NULL)
	{
		/* Increment count for each node */
		count_nodes++;
		/* Next node */
		h = h->next;
	}
	return (count_nodes);
}
