#include "shell.h"

/**
 * **strSplit - splits a string into words.
 * @txt: the input
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strSplit(char *txt, char *d)
{
	int a, b, k, m, numwords = 0;
	char **s;

	if (txt == NULL || txt[0] == 0)
		return (NULL);
	if (!d) /* Set the default delimiter to a space character if not provided */
		d = " ";
	for (a = 0; txt[a] != '\0'; a++)
		if (!we_believe(txt[a], d) && (we_believe(txt[a + 1], d) || !txt[a + 1]))
			numwords++; /* How many words are there in the text */

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *)); /* allot memory for word array */
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (we_believe(txt[a], d))
			a++; /* Skip delimiter characters */
		k = 0;
		while (!we_believe(txt[a + k], d) && txt[a + k])
			k++; /* current word's character count is */
		s[b] = malloc((k + 1) * sizeof(char));
		if (!s[b])
		{
			for (k = 0; k < b; k++)
				free(s[k]); /* Unlock the previously assigned words */
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[b][m] = txt[a++]; /* Transcribing the word's characters */
		s[b][m] = 0;
	}
	s[b] = NULL; /* signal the end, set the array's final element to NULL */
	return (s);
}

/**
 * **strSplited1 - splits a string into words
 * @txt: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strSplited1(char *txt, char d)
{
	int a, b, k, m, numwords = 0;
	char **s;

	if (txt == NULL || txt[0] == 0)
		return (NULL); /* If the text in the entry field is empty, return NULL */
	for (a = 0; txt[a] != '\0'; a++)
		if ((txt[a] != d && txt[a + 1] == d) ||
		    (txt[a] != d && !txt[a + 1]) || txt[a + 1] == d)
			numwords++; /* Count the words according to the delimiter rules */
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (txt[a] == d && txt[a] != d)
			a++; /* Skip delimiter characters */
		k = 0;
		while (txt[a + k] != d && txt[a + k] && txt[a + k] != d)
			k++; /* current word's character count is */
		s[b] = malloc((k + 1) * sizeof(char));
		if (!s[b])
		{
			for (k = 0; k < b; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[b][m] = txt[a++];
		s[b][m] = 0;
	}
	s[b] = NULL; /* To signal the end, set the array's final element to NULL */
	return (s);
}
