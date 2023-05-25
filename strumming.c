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

	(void)data;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
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
		if (pathstr[a] != ':')
			buffed[k++] = pathstr[a];
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
	if ((stringLen(cmd) > 2) && beginWith(cmd, "./"))
	{
		if (thisCmd(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = duplicationJustu(pathstr, curr_pos, a);
			if (!*path)
				strConcat(path, cmd);
			else
			{
				strConcat(path, "/");
				strConcat(path, cmd);
			}
			if (thisCmd(data, path))
				return (path);
			if (!pathstr[a])
				break;
			curr_pos = a;
		}
		a++;
	}
	return (NULL);
}
