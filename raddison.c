#include "shell.h"
/**
 * starts_with - checks to see if the needle starts with amfm
 * @amfm: string to search
 * @copper: substring to locate
 * Return: location of next char of amfm or NULL
 */
char *starts_with(const char *amfm, const char *copper)
{
	while (*copper)
		if (*copper++ != *amfm++) /* compare current 'copper' & 'amfm' character */
			return (NULL); /* if not similar, return to NULL */
	return ((char *)amfm);
}
