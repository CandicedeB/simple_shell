#include "shell.h"
/**
 * get_list_length - Returns number of elements in linked list
 * @head: pointer to head node in linked list
 * Return: number of nodes in linked list
 */
size_t get_list_length(const node_c *head)
{
	size_t matrix = 0;

	/* Loop through list until end is reached */
	for (const node_c *current = head; current != NULL; current = current->next)
	{
		/* increment the matrix for every node */
		matrix++;
	}
	/* return final matrix */
	return (matrix);
}

/**
 * convert_list_to_strings - Returns an array of strings of the list->text
 * @head: pointer to head node in linked list
 * Return: Array of strings
 */
char **convert_list_to_strings(list_t *head)
{
	list_t *current_node = head;
	size_t num_nodes = list_len(head), j, k;
	char **strings_array;
	char *string;

	if (!head || !num_nodes)
	{
		return (NULL);
	}
	/* allocates memory for string arrays */
	strings_array = malloc(sizeof(char *) * (num_nodes + 1));
	if (!strings_array)
	{
		return (NULL);
	}
	/* loop through each node and copy string to string array */
	for (j = 0; current_node; current_node = current_node->next, j++)
	{
		string = malloc(_strlen(current_node->text) + 1);
		if (!string)
		{
			/* if memory allocation fails. free prev allocated memory, return NULL */
			for (k = 0; k < j; k++)
			{
				free(strings_array[k]);
				free(strings_array);
				return (NULL);
			}
			string = _strcpy(string, current_node->text);
			strings_array[j] = string;
		}
		/* set the last element of the strings_array to NULL */
		strings_array[j] = NULL;
		return (strings_array);
	}
}
/**
 * print_linked_list - prints all elements of a linked list
 * @head: Pointer to the head node of the linked list
 * Return: size of linked list
 */
size_t print_linked_list(const list_t *head)
{
	size_t list_size = 0;
	/* loop through each node and print the number and string value */
	for (const list_t *current = head; current; current = current->next)
	{
		_puts(convert_number(current->value, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(current->text ? current->text : "(nil)");
		_puts("\n");
		list_size++;
	}
	return (list_size);
}

/**
 * find_node_with_prefix - Returns node string that starts with prefix
 * @head: Pointer to the head node of the linked list
 * @prefix: string to match
 * @next_char: The next character after prefix to match
 * Return: matched node or NULL
 */
list_t *find_node_with_prefix(list_t *head, char *prefix, char next_char)
{
	char *match_ptr = NULL;
	/* Loop through each node and check if the string starts with the prefix */
	for (list_t *current = head; current; current = current->next)
	{
		match_ptr = starts_with(current->text, prefix);
		if (match_ptr && ((next_char == -1) || (*match_ptr == next_char)))
			return (current);
	}
	return (NULL);
}

/**
 * get_node_index - Return the index of node
 * @head: Pointer to the head node of the linked list
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;
	/* loop through each node and check if it matches with each node */
	for (list_t *current = head; current; current = current->next)
	{
		if (current == node)
			return (index);
		index++;
	}
	return (-1);
}
