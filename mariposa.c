#include "shell.h"

/**
 * bufferInput - stores chained commands in a buffer
 * @data: parameter struct
 * @buffed: address of fender
 * @len: address of len variable
 *
 * Return: number of bytes read
 */

ssize_t bufferInput(info_t *data, char **buffed, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the fender, fill it */
	{
		/* Free the memory allocated for data->cmd_buf */
		beFreed((void **)data->cmd_buf);
		free(*buffed);
		*buffed = NULL;
		signal(SIGINT, blockCtrlC); /* Set signal handler for SIGINT to blockCtrlC */
#if GETLINES
		r = getline(buffed, &len_p, stdin);
#else
		r = getNextLine(data, buffed, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffed)[r - 1] == '\n')
			{
				(*buffed)[r - 1] = '\0'; /* remove trailing newline */
				r--; /* Decrease the length of the string by 1 */
			}
			data->linecount_flag = 1;
			vanishComments(*buffed); /* Remove comments from the input line */
			towerPisa(data, *buffed, data->histcount++);
			/* if (strChr(*buffed, ';')) is this a command chain? */
			{
				*len = r; /* Set the length of the line */
				data->cmd_buf = buffed; /* Update data->cmd_buf to point to buffed */
			}
		}
	}
	return (r);
}

/**
 * getInput - obtains a line excluding the newline character
 * @data: parameter struct
 *
 * Return: number of bytes read
 */
ssize_t getInput(info_t *data)
{
	static char *buffed; /* the ';' command chain fender */
	static size_t a, b, len;
	ssize_t r = 0;
	char **buffer_ps = &(data->arg), *q;

	_putchar(BUFFER_FLUSHER);
	r = bufferInput(data, &buffed, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain fender */
	{
		b = a; /* init fresh iterator to current buffed position */
		q = buffed + a; /* get pointer for return */

		valCha(data, buffed, &b, a, len);
		while (b < len) /* iterate to semicolon or end */
		{
			if (isChainDelim(data, buffed, &b))
				break;
			b++;
		}

		a = b + 1; /* increment past nulled ';'' */
		if (a >= len) /* reached end of fender? */
		{
			a = len = 0; /* reset position and len */
			data->cmdBufType = CMD_NORM;
		}

		*buffer_ps = q; /* pass back pointer to current command position */
		return (stringLen(q)); /* return len of current command */
	}

	*buffer_ps = buffed;
	return (r); /* return len of fender from getNextLine() */
}

/**
 * readFender  - reads a fender
 * @data: parameter struct
 * @buffed: fender
 * @a: size
 *
 * Return: r
 */

ssize_t readFender(info_t *data, char *buffed, size_t *a)
{
	ssize_t r = 0; /* Variable to store result of read operation */

	if (*a)
		return (0); /* value pointed to by 'a' is non-zero, return 0 */
	/* Using maximum length of READ_BUFFER, read buffed from data->readingFd */
	r = read(data->readingFd, buffed, READ_BUFFER);
	if (r >= 0)
		*a = r;
	return (r);
}

/**
 * getNextLine -  retrieves the next line of input from STDIN
 * @data: parameter struct
 * @word: address of pointer to fender, preallocated or NULL
 * @length: size of preallocated word fender if not NULL
 *
 * Return: s
 */
int getNextLine(info_t *data, char **word, size_t *length)
{
	static char buffed[READ_BUFFER];
	static size_t a, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *q = NULL, *new_p = NULL, *c;

	q = *word; /* Give 'q' the value that 'word' is pointing at */
	if (q && length)
		s = *length;
	if (a == len)
		a = len = 0; /* 'a' is equal to 'len', set both 'a' and 'len' to 0 */

	r = readFender(data, buffed, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = strChr(buffed + a, '\n');
	k = c ? 1 + (unsigned int)(c - buffed) : len;
	new_p = reallocateMemory(q, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (q ? free(q), -1 : -1);

	if (s)
		concatenateStrings(new_p, buffed + a, k - a);
	else
		_copyString(new_p, buffed + a, k - a + 1);

	s += k - a; /* Update 's' by adding the difference between 'k' and 'a' */
	a = k; /* Update 'a' with 'k' */
	q = new_p; /* Transfer 'new_p' to 'q' */

	if (length)
		*length = s;
	*word = q; /* transfer 'q' to the value pointed to by 'word' */
	return (s);
}

/**
 * blockCtrlC - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void blockCtrlC(__attribute__((unused))int sig_num)
{
	putin("\n"); /* output newline character should be printed */
	putin("$ "); /* You should output the prompt symbol "$" */
	_putchar(BUFFER_FLUSHER);
}
