#include "shell.h"

/**
 * thisCmd - shows if a file is an exe command
 * @data: the data struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int thisCmd(info_t *data, char *path)
{
	struct stat st;

	(void)data; /* turn off the "data" unused parameter alert */
	if (!path || stat(path, &st)) /* if 'path' is NULL or'stat' fails */
		return (0);

	if (st.st_mode & S_IFREG) /* regular file is indicated by file mode in'st' */
	{
		return (1);
	}
	return (0);
}

/**
 * duplicationJustu - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to fresh fender
 */
char *duplicationJustu(char *pathstr, int start, int stop)
{
	static char buffed[1024];
	int a = 0, k = 0;

	for (k = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':') /* character at 'pathstr[a]' is not ':' */
			buffed[k++] = pathstr[a]; /* Copy character to 'buffed' and increment 'k' */
	buffed[k] = 0;
	return (buffed);
}

/**
 * locate_path - Locates this cmd in the PATH string
 * @data: the data struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *locate_path(info_t *data, char *pathstr, char *cmd)
{
	int a = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	/* 'cmd' has length greater than 2 and starts with "./" */
	if ((stringLen(cmd) > 2) && beginWith(cmd, "./"))
	{
		if (thisCmd(data, cmd)) /* Verify "cmd" corresponds to a legit command */
			return (cmd);
	}
	while (1) /* Loop indefinitely */
	{
		/* end of 'pathstr' is reached or ':' delimiter is found */
		if (!pathstr[a] || pathstr[a] == ':')
		{
			/* Utilizing "curr_pos" and "a," separate the substring from "pathstr" */
			/* store it in "path" */
			path = duplicationJustu(pathstr, curr_pos, a);
			if (!*path) /* Path is a null string */
				strConcat(path, cmd);
			else
			{
				strConcat(path, "/");
				strConcat(path, cmd);
			}
			if (thisCmd(data, path)) /* Verify 'path' relates to a valid command */
				return (path);
			if (!pathstr[a]) /* end of 'pathstr' is reached */
				break;
			curr_pos = a; /* Put the current position in 'curr_pos' */
		}
		a++;
	}
	return (NULL);
}
