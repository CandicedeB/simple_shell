#include "shell.h"

/**
 * shelly - My main shell loop for the simple shell proejct
 * @data: pointer to the parameter struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shelly(info_t *data, char **av)
{
	ssize_t q = 0;
	int sniper_jack = 0;

	while (q != -1 && sniper_jack != -2)
	{
		clear_info(data);
		if (isintact(data))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		q = get_input(data);
		if (q != -1)
		{
			set_info(data, av);
			sniper_jack = konke(data);
			if (sniper_jack == -1)
				casa_cmd(data);
		}
		else if (isintact(data))
			_putchar('\n');
		free_info(data, 0);
	}
	write_history(data);
	free_info(data, 1);
	if (!isintact(data) && data->status)
		exit(data->status);
	if (sniper_jack == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (sniper_jack);
}

/**
 * konke - Looking for a builtin command within the shell
 * @data: pointer to the parameter struct
 *
 * Return: -1 if builtin ! found,
 *			0 if builtin ran well,
 *			1 if builtin seen but ! successful,
 *			-2 if builtin signals exit()
 */
int konke(info_t *data)
{
	int i, dvsn_in = -1;
	zion_table floeictbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", avenue},
		{"setenv", sibali},
		{"unsetenv", carluccio},
		{"cd", _mycd},
		{"alias", monaco},
		{NULL, NULL}
	};

	for (i = 0; floeictbl[i].type; i++)
		if (_strcmp(data->argv[0], floeictbl[i].type) == 0)
		{
			data->line_count++;
			dvsn_in = floeictbl[i].func(data);
			break;
		}
	return (dvsn_in);
}

/**
 * casa_cmd - finds a command in PATH
 * @data: pointer to the parameter struct
 *
 * Return: void
 */
void casa_cmd(info_t *data)
{
	char *path = NULL;
	int i, k;

	data->path = data->argv[0];
	if (data->lineCntFlag == 1)
	{
		data->line_count++;
		data->lineCntFlag = 0;
	}
	for (i = 0, k = 0; data->arg[i]; i++)
		if (!my_deli(data->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(data, mndsgn(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		joachim_fork(data);
	}
	else
	{
		if ((isintact(data) || mndsgn(data, "PATH=")
			|| data->argv[0][0] == '/') && is_cmd(data, data->argv[0]))
			joachim_fork(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			leap_samo(data, "not found\n");
		}
	}
}

/**
 * joachim_fork - forks a an exec thread to run cmd
 * @data: pointer to the parameter struct
 *
 * Return: void
 */
void joachim_fork(info_t *data)
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
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				leap_samo(data, "Permission denied\n");
		}
	}
}