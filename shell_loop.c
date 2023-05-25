#include "shell.h"

/**
 * hsh - main shell loop
 * @data: the parameter & return data struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *data, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(data);
		if (invlove(data))
			putin("$ ");
		eputword(BUFFER_FLUSHER);
		r = getInput(data);
		if (r != -1)
		{
			set_info(data, av);
			builtin_ret = find_builtin(data);
			if (builtin_ret == -1)
				find_cmd(data);
		}
		else if (invlove(data))
			_putchar('\n');
		free_info(data, 0);
	}
	write_history(data);
	free_info(data, 1);
	if (!invlove(data) && data->worth)
		exit(data->worth);
	if (builtin_ret == -2)
	{
		if (data->err_num == -1)
			exit(data->worth);
		exit(data->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @data: the parameter & return data struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *data)
{
	int a, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", shellExit},
		{"env", printMyEnv},
		{"help", showHelp},
		{"history", displayHistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", changeDir},
		{"alias", mineAlias},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (_strcmps(data->argv[0], builtintbl[a].type) == 0)
		{
			data->line_count++;
			built_in_ret = builtintbl[a].func(data);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @data: the parameter & return data struct
 *
 * Return: void
 */
void find_cmd(info_t *data)
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

	path = find_path(data, findEnv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		fork_cmd(data);
	}
	else
	{
		if ((invlove(data) || findEnv(data, "PATH=")
			|| data->argv[0][0] == '/') && is_cmd(data, data->argv[0]))
			fork_cmd(data);
		else if (*(data->arg) != '\n')
		{
			data->worth = 127;
			display_err(data, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @data: the parameter & return data struct
 *
 * Return: void
 */
void fork_cmd(info_t *data)
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
		if (execve(data->path, data->argv, get_environ(data)) == -1)
		{
			free_info(data, 1);
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
