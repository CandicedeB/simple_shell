#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @data: the data struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *data, char *path)
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
 * dup_chars - duplicates characters
 * @pathtxt: the PATH string
 * @begin: starting index
 * @end: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathtxt, int begin, int end)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = begin; i < end; i++)
		if (pathtxt[i] != ':')
			buf[k++] = pathtxt[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @data: the data struct
 * @pathtxt: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *data, char *pathtxt, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathtxt)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathtxt[i] || pathtxt[i] == ':')
		{
			path = dup_chars(pathtxt, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(data, path))
				return (path);
			if (!pathtxt[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}