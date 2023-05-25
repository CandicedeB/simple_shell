#include "shell.h"

/**
 * bufferInput - stores chained commands in a buffer
 * @data: parameter struct
 * @buffed: address of fender
 * @length: address of length variable
 *
 * Return: number of bytes read
 */

ssize_t bufferInput(info_t *data, char **buffed, size_t *length)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*length) /* if nothing left in the fender, fill it */
	{
		/*beFreed((void **)data->cmd_buf);*/
		free(*buffed);
		*buffed = NULL;
		signal(SIGINT, blockCtrlC);
#if USE_GETLINE
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
			remove_comments(*buffed);
			build_history_list(data, *buffed, data->histcount++);
			/* if (strChr(*buffed, ';')) is this a command chain? */
			{
				*length = r;
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
	static size_t a, b, length;
	ssize_t r = 0;
	char **buffer_ps = &(data->arg), *q;

	_putchar(BUFFER_FLUSHER);
	r = bufferInput(data, &buffed, &length);
	if (r == -1) /* EOF */
		return (-1);
	if (length)	/* we have commands left in the chain fender */
	{
		b = a; /* init fresh iterator to current buffed position */
		q = buffed + a; /* get pointer for return */

		validateChain(data, buffed, &b, a, length);
		while (b < length) /* iterate to semicolon or end */
		{
			if (isChainDelim(data, buffed, &b))
				break;
			b++;
		}

		a = b + 1; /* increment past nulled ';'' */
		if (a >= length) /* reached end of fender? */
		{
			a = length = 0; /* reset position and length */
			data->cmdBufType = CMD_NORM;
		}

		*buffer_ps = q; /* pass back pointer to current command position */
		return (_strlen(q)); /* return length of current command */
	}

	*buffer_ps = buffed; /* else not a chain, pass back fender from getNextLine() */
	return (r); /* return length of fender from getNextLine() */
}

/**
 * readFender  - reads a fender
 * @data: parameter struct
 * @buffed: fender
 * @a: size
 *
 * Return: r
 */

ssize_t readFender (info_t *data, char *buffed, size_t *a)
{
	ssize_t r = 0;

	if (*a)
		return (0);
	r = read(data->readingFd, buffed, READ_BUFFER_SIZE);
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
	static char buffed[READ_BUFFER_SIZE];
	static size_t a, length;
	size_t k;
	ssize_t r = 0, s = 0;
	char *q = NULL, *new_p = NULL, *c;

	q = *word;
	if (q && length)
		s = *length;
	if (a == length)
		a = length = 0;

	r = readFender (data, buffed, &length);
	if (r == -1 || (r == 0 && length == 0))
		return (-1);

	c = strChr(buffed + a, '\n');
	k = c ? 1 + (unsigned int)(c - buffed) : length;
	new_p = reallocateMemory(q, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (q ? free(q), -1 : -1);

	if (s)
		concatenateStrings(new_p, buffed + a, k - a);
	else
		copyString(new_p, buffed + a, k - a + 1);

	s += k - a;
	a = k;
	q = new_p;

	if (length)
		*length = s;
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