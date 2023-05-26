#include "shell.h"

/**
 * getHistoryFile - gets the history file
 * @data: parameter struct
 *
 * Return: allocated string containg history file
 */

char *getHistoryFile(info_t *data)
{
	char *buffed, *dir;
	/* environment variable is not found, return NULL */
	dir = findEnv(data, "HOME=");
	if (!dir)
		return (NULL);
	/* Allocate memory for the concatenated path */
	buffed = malloc(sizeof(char) * (stringLen(dir) + stringLen(JIST_FILED) + 2));
	if (!buffed) /* memory allocation fails, return NULL */
		return (NULL);
	buffed[0] = 0; /* Initialize the buffer as an empty string */
	copyString(buffed, dir); /* Copy the "dir" string to the buffer */
	strConcat(buffed, "/"); /* Concatenate a forward slash to the buffer */
	strConcat(buffed, JIST_FILED);
	return (buffed);
}

/**
 * genHistory - creates a file, or appends to an existing file
 * @data: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int genHistory(info_t *data)
{
	ssize_t fd;
	char *filename = getHistoryFile(data);
	list_t *list = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename); /* Free the memory allocated for the filename */
	/* Check if file descriptor is -1 (indicating an error in open file) */
	if (fd == -1)
		return (-1); /* If so, return -1 */
	for (list = data->history; list; list = list->next)
	{
		putsFdk(list->txt, fd); /* Write text of each history entry to file */
		putFd('\n', fd); /* Write a newline character to file */
	}
	putFd(BUFFER_FLUSHER, fd);
	close(fd); /* Close the file */
	return (1);
}

/**
 * cramHis - reads history from file
 * @data: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int cramHis(info_t *data)
{
	int a, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffed = NULL, *filename = getHistoryFile(data);

	if (!filename)
		return (0);
	/* Open the file with the given filename in read-only mode */
	fd = open(filename, O_RDONLY);
	free(filename); /* Free memory allocated for filename */
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st)) /* Retrieve information about file, including its size */
		fsize = st.st_size; /* Store the file size in the variable "fsize" */
	if (fsize < 2) /* Check if the file size is less than 2 */
		return (0);
	buffed = malloc(sizeof(char) * (fsize + 1));
	if (!buffed) /* Check if memory allocation failed */
		return (0);
	rdlen = read(fd, buffed, fsize); /* Read contents of the file into buffer */
	buffed[fsize] = 0; /* null-terminating character at end of the buffer */
	if (rdlen <= 0)
		return (free(buffed), 0);
	close(fd); /* Close the file */
	for (a = 0; a < fsize; a++) /* Iterate through buffer to process each line */
		if (buffed[a] == '\n')
		{
			buffed[a] = 0;
			/* Process the line using the towerPisa function */
			towerPisa(data, buffed + last, linecount++);
			last = a + 1; /* Update the "last" variable to point to the next line */
		}
	if (last != a) /* Check if there is a line remaining after the loop */
		towerPisa(data, buffed + last, linecount++); /* Process the remaining line */
	free(buffed);
	data->histcount = linecount;
	while (data->histcount-- >= JIST_OVERFLOW)
		delNodeatIndex(&(data->history), 0);
	numKimbad(data); /* Perform further processing on the data */
	return (data->histcount);
}

/**
 * towerPisa - adds entry to a history linked list
 * @data: Structure containing potential arguments. Used to maintain
 * @buffed: fender
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int towerPisa(info_t *data, char *buffed, int linecount)
{
	list_t *list = NULL;

	if (data->history) /* Check if data structure has existing history entries */
		list = data->history; /* assign existing history list to "list" variable */
	add_node_finish(&list, buffed, linecount);
	/* Check if the data structure had no existing history entries */
	if (!data->history)
		data->history = list;
	return (0); /* Return 0 to indicate successful execution */
}

/**
 * numKimbad - renumbers the history linked list after changes
 * @data: Structure containing potential arguments. Used to maintain
 *
 * Return: the fresh histcount
 */
int numKimbad(info_t *data)
{
	list_t *list = data->history;
	int a = 0;

	while (list)
	{
		/* Assign a unique number to "num" field of each node and increment "a" */
		list->num = a++;
		list = list->next; /* Move to the next node in the list */
	}
	return (data->histcount = a);
}
