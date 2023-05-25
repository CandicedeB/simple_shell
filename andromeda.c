#include "shell.h"

/**
 * shellExit - exits the shell
 * @data: Structure containing relevant arguments for function
 * Return: Exits the shell with a specific exit worth (0)
 * if data.argv[0] is not "exit"
 */
int shellExit(info_t *data)
{
	int leaveVerify;

	if (data->argv[1])
	{
		leaveVerify = errAtoi(data->argv[1]);
		if (leaveVerify == -1)
		{
			data->worth = 2;
			display_err(data, "Wrong number: ");
			eputin(data->argv[1]);
			eputword('\n');
			return (1);
		}
		data->digit_err = errAtoi(data->argv[1]);
		return (-2);
	}
	data->digit_err = -1;
	return (-2);
}

/**
 * changeDir - modifies the current directory of the process
 * @data: Structure containing relevant arguments for the function
 *  Return: Always 0
 */
int changeDir(info_t *data)
{
	char *s, *dir, fender[1024];
	int fgdir_look;

	s = getcwd(fender, 1024);
	if (!s)
		putin("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		dir = findEnv(data, "HOME=");
		if (!dir)
			fgdir_look = /* TODO: what should this be? */
				chdir((dir = findEnv(data, "PWD=")) ? dir : "/");
		else
			fgdir_look = chdir(dir);
	}
	else if (_strcmps(data->argv[1], "-") == 0)
	{
		if (!findEnv(data, "OLDPWD="))
		{
			putin(s);
			_putchar('\n');
			return (1);
		}
		putin(findEnv(data, "OLDPWD=")), _putchar('\n');
		fgdir_look = /* TODO: what should this be? */
			chdir((dir = findEnv(data, "OLDPWD=")) ? dir : "/");
	}
	else
		fgdir_look = chdir(data->argv[1]);
	if (fgdir_look == -1)
	{
		display_err(data, "can't cd to ");
		eputin(data->argv[1]), eputword('\n');
	}
	else
	{
		fixEnv(data, "OLDPWD", findEnv(data, "PWD="));
		fixEnv(data, "PWD", getcwd(fender, 1024));
	}
	return (0);
}

/**
 * showHelp - provides assistance and information
 * @data: Structure containing relevant arguments for the function
 * Return: Always 0
 */
int showHelp(info_t *data)
{
	char **arg_array;

	arg_array = data->argv;
	putin("help call works. Function not yet implemented \n");
	if (0)
		putin(*arg_array); /* temp att_unused workaround */
	return (0);
}
