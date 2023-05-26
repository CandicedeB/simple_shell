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

	while (r != -1 && innerRet != -2) /* when 'r' & 'innerRet', not -1 and -2 */
	{
		cleanData(data); /* 'Data' cleanup */
		if (invlove(data)) /* Verify whether 'data' is involved */
			putin("$ "); /* Obtain input, then save the outcome in "r" */
		eputword(BUFFER_FLUSHER);
		r = getInput(data); /* Obtain input, then save the outcome in "r" */
		if (r != -1)
		{
			fixData(data, av);
			/* Find the interior of 'data' and save the outcome in 'innerRet' */
			innerRet = locateInner(data);
			if (innerRet == -1)
				lookForCmd(data);
		}
		else if (invlove(data))
			_putchar('\n');
		freeData(data, 0); /* Free the "data" without also liberating the past */
	}
	genHistory(data); /* 'Data'-based history generation */
	freeData(data, 1); /* 'Data' should be made available, including history */
	if (!invlove(data) && data->worth)
		exit(data->worth); /* 'data->worth' should be the status when you exit */
	if (innerRet == -2)
	{
		if (data->digit_err == -1)
			exit(data->worth);
		exit(data->digit_err); /* 'data->digit_err' will be checked when you exit */
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
	/* Declare variables 'a' and 'inBuiltRet' and initialize 'inBuiltRet' to -1 */
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
	/* Go over the innerLib array iteratively */
	for (a = 0; innerLib[a].type; a++)
		if (_strcmps(data->argv[0], innerLib[a].type) == 0)
		{
			data->line_count++;
			inBuiltRet = innerLib[a].func(data); /* Call the matching innerLib */
			/* function and place the result in the 'inBuiltRet' variable */
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

	data->path = data->argv[0]; /* Set 'data->path' to 1st argument of 'data' */
	if (data->linecount_flag == 1) /* 'data->linecount_flag' is 1 */
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (a = 0, k = 0; data->arg[a]; a++) /* Iterate the 'arg' array of 'data' */
		/*  event that 'data->arg[a]' doesn't have any whitespace characters */
		if (!we_believe(data->arg[a], " \t\n"))
			k++;
	if (!k)
		return;

	path = locate_path(data, findEnv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path; /* Update 'data->path' with 'path' */
		forkingCmd(data);
	}
	else
	{
		if ((invlove(data) || findEnv(data, "PATH=")
			|| data->argv[0][0] == '/') && thisCmd(data, data->argv[0]))
			forkingCmd(data); /* certain criteria are met, call "forkingCmd" function */
		else if (*(data->arg) != '\n')
		{
			data->worth = 127; /* Set 'data->worth' to 127 */
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
	/* Make a child process, then save process ID in "child_pid" variable */
	child_pid = fork();
	if (child_pid == -1) /* fork() returns -1 (indicating an error) */
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		/* Execute command using execve() */
		if (execve(data->path, data->argv, getEnviron(data)) == -1)
		{
			freeData(data, 1);
			if (errno == EACCES) /* error is due to permission denied */
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else /* current process is the parent process */
	{
		/* Keep an eye out for the child process to end, */
		/* then record the exit status in "data->worth */
		wait(&(data->worth));
		if (WIFEXITED(data->worth)) /* child process terminated normally */
		{
			data->worth = WEXITSTATUS(data->worth);
			if (data->worth == 126)
				display_err(data, "Permission denied\n");
		}
	}
}
