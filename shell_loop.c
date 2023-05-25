#include "shell.h"

/**
 * hsh - my main shell loop
 * @data: the parameter and return data struct
 * @av: the argument vector
 *
 * Return: 0 success, 1 error, or error code
 */
int hsh(info_t *data, char **av)
{
	ssize_t r = 0;
	int innerRet = 0;

	while (r != -1 && innerRet != -2)
	{
		cleanData(data);
		if (invlove(data))
			putin("$ ");
		eputword(BUFFER_FLUSHER);
		r = getInput(data);
		if (r != -1)
		{
			fixData(data, av);
			innerRet = locateInner(data);
			if (innerRet == -1)
				lookForCmd(data);
		}
		else if (invlove(data))
			_putchar('\n');
		freeData(data, 0);
	}
	genHistory(data);
	freeData(data, 1);
	if (!invlove(data) && data->worth)
		exit(data->worth);
	if (innerRet == -2)
	{
		if (data->digit_err == -1)
			exit(data->worth);
		exit(data->digit_err);
	}
	return (innerRet);
}

/**
 * locateInner - Locate a builtin command
 * @data: data struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int locateInner(info_t *data)
{
	int a, inBuiltRet = -1;
	innerTable innerLib[] = {
		{"exit", shellExit},
		{"env", printMyEnv},
		{"help", showHelp},
		{"history", displayHistory},
		{"setenv", setEnvVar},
		{"unsetenv", removeEnvVar},
		{"cd", changeDir},
		{"alias", mineAlias},
		{NULL, NULL}
	};

	for (a = 0; innerLib[a].type; a++)
		if (_strcmps(data->argv[0], innerLib[a].type) == 0)
		{
			data->line_count++;
			inBuiltRet = innerLib[a].func(data);
			break;
		}
	return (inBuiltRet);
}

/**
 * lookForCmd - locate a command in PATH
 * @data: the parameter & return data struct
 *
 * Return: void
 */
void lookForCmd(info_t *data)
{
	char *path = NULL;
	int a, k;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (a = 0, k = 0; data->arg[a]; a++)
		if (!we_believe(data->arg[a], " \t\n"))
			k++;
	if (!k)
		return;

	path = locate_path(data, findEnv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		forkingCmd(data);
	}
	else
	{
		if ((invlove(data) || findEnv(data, "PATH=")
			|| data->argv[0][0] == '/') && thisCmd(data, data->argv[0]))
			forkingCmd(data);
		else if (*(data->arg) != '\n')
		{
			data->worth = 127;
			display_err(data, "not found\n");
		}
	}
}

/**
 * forkingCmd - forks a an exec thread to run cmd
 * @data: the parameter & return data struct
 *
 * Return: void
 */
void forkingCmd(info_t *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, getEnviron(data)) == -1)
		{
			freeData(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(data->worth));
		if (WIFEXITED(data->worth))
		{
			data->worth = WEXITSTATUS(data->worth);
			if (data->worth == 126)
				display_err(data, "Permission denied\n");
		}
	}
}
