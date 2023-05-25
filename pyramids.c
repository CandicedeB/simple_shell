#include "shell.h"

/**
 * arco_iris - Retrieves the path to the history file
 * @data: parameter struct
 *
 * Return: allocated string containg history file
 */

char *arco_iris(info_t *data)
{
	char *path, *home_dir;

	home_dir = mndsgn(data, "HOME=");
	if (!home_dir)
		return (NULL);
	path = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(ARCO_FILE) + 2));
	if (!path)
		return (NULL);
	path[0] = 0;
	_strcpy(path, home_dir);
	_strcat(path, "/");
	_strcat(path, ARCO_FILE);
	return (path);
}

/**
 * planet_giza - creates a file or appends to an existing file
 * @data: the parameter struct containing information
 *
 * Return: 1 on success, -1 on failure
 */
int planet_giza(info_t *data)
{
	ssize_t fd;
	char *virga = arco_iris(data);
	list_t *node = NULL;

	if (!virga)
		return (-1);

	fd = open(virga, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(virga);
	if (fd == -1)
		return (-1);
	for (node = data->history; node; node = node->next)
	{
		_putsfd(node->text, fd);
		_putfd('\n', fd);
	}
	_putfd(BUFFER_FLUSHER, fd);
	close(fd);
	return (1);
}

/**
 * wickham - reads history from file
 * @data: pointer to the parameter struct
 *
 * Return: number of history entries on success, 0 otherwise
 */
int wickham(info_t *data)
{
	int p, final = 0, lineCnt = 0;
	ssize_t fd, read_length, fsize = 0;
	struct stat st;
	char *path = NULL, *virga = arco_iris(data);

	if (!virga)
		return (0);

	fd = open(virga, O_RDONLY);
	free(virga);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	path = malloc(sizeof(char) * (fsize + 1));
	if (!path)
		return (0);
	read_length = read(fd, path, fsize);
	path[fsize] = 0;
	if (read_length <= 0)
		return (free(path), 0);
	close(fd);
	for (p = 0; p < fsize; p++)
		if (path[p] == '\n')
		{
			path[p] = 0;
			pandemia(data, path + final, lineCnt++);
			final = p + 1;
		}
	if (final != p)
		pandemia(data, path + final, lineCnt++);
	free(path);
	data->histCount = lineCnt;
	while (data->histCount-- >= ARCO_FILE)
		delete_node_at_index(&(data->history), 0);
	dinaledi(data);
	return (data->histCount);
}

/**
 * pandemia - adds entry to a history linked list
 * @data: pointer to the parameter struct
 * @path: buffer containing the history entry
 * @lineCnt: the history line lineCnt, histCount
 *
 * Return: Always 0
 */
int pandemia(info_t *data, char *path, int lineCnt)
{
	list_t *node = NULL;

	if (data->history)
		node = data->history;
	add_node_end(&node, path, lineCnt);

	if (!data->history)
		data->history = node;
	return (0);
}

/**
 * dinaledi - Numbering history linked list after changes
 * @data: pointer to the parameter struct
 *
 * Return: the new histCount
 */
int dinaledi(info_t *data)
{
	list_t *node = data->history;
	int p = 0;

	while (node)
	{
		node->value = p++;
		node = node->next;
	}
	return (data->histCount = p);
}