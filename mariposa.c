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
		beFreed((void **)data->cmd_buf);
		free(*buffed);
		*buffed = NULL;
		signal(SIGINT, blockCtrlC);
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
				r--;
			}
			data->linecount_flag = 1;
			vanishComments(*buffed);
			towerPisa(data, *buffed, data->histcount++);
			/* if (strChr(*buffed, ';')) is this a command chain? */
			{
				*len = r;
				data->cmd_buf = buffed;
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
	ssize_t r = 0;

	if (*a)
		return (0);
	r = read(data->readingFd, buffed, READ_BUFFER);
	if (r >= 0)
		*a = r;
	return (r);
}

/**
 * getNextLine -  retrieves the next line of input from STDIN
 * @data: parameter struct
 * @word: address of pointer to fender, preallocated or NULL
 * @len: size of preallocated word fender if not NULL
 *
 * Return: s
 */
int getNextLine(info_t *data, char **word, size_t *len)
{
	static char buffed[READ_BUFFER];
	static size_t a, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *q = NULL, *new_p = NULL, *c;

	q = *word;
	if (q && len)
		s = *len;
	if (a == len)
		a = len = 0;

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

	s += k - a;
	a = k;
	q = new_p;

	if (len)
		*len = s;
	*word = q;
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
	putin("\n");
	putin("$ ");
	_putchar(BUFFER_FLUSHER);
}
