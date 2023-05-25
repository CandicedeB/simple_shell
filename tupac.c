#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t data[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd) 
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				eputin(av[0]);
				eputin(": 0: Can't open ");
				eputin(av[1]);
				eputword('\n');
				eputword(BUFFER_FLUSHER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readingFd = fd;
	}
	filEnvList(data);
	cramHis(data);
	hsh(data, av);
	return (EXIT_SUCCESS);
}
