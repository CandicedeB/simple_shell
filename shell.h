#ifndef SHELL_H
#define SHELL_H

#define MAX_ARGS 64
#define BUFFER 1024 /* define constant buffer of 1024 bytes */

/* Library Used */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * struct listnode - singly linked list node
 * @value: the value stored in the node
 * @text: a string associated with the value
 * @next: pointer to the next node in the list
 */
typedef struct listnode
{
	int value;
	char *text;
	struct listnode *next;
} list_t;

/**
 * cmd_info - contains arguments to be passed into a function
 * @argv: an array of strings containing the command arguments
 * @readFd: the file descriptor from which to read line input
 * @lineCntFlag: set to 1 to count this line of input
 * @history: the history linked list node
 * @path: the path of the current command
 * @environ: custom modified copy of the environment variables from the linked list env
 * @arg: a string containing the command arguments generated from getline
 * @lineCnt: the line count of the input
 * @alias: the alias linked list node
 * @envChanged: set to 1 if the environment variables were modified
 * @cmdBufType: the type of command buffer: CMD_type ||, &&, ;
 * @env: the linked list containing the local copy of the environment variables
 * @cmdBuf: a pointer to the command ; chain buffer, used for memory management
 * @status: the return status of the last executed command
 * @argc: the argument count
 * @fname: the filename of the program
 * @errNum: the error code for exit() calls
 * @histCount: the history line number count
 */
typedef struct cmd_info
{
	char **argv;
	int readFd;
	int lineCntFlag;
	list_t *history;
	char *path;
	char **environ;
	char *arg;
	unsigned int lineCnt;
	list_t *alias;
	int envChanged;
	int cmdBufType;
	list_t *env;
	char **cmdBuf;
	int status;
	int argc;
	char *fname;
	int errNum;
	int histCount;
} info_t;

/* Prototypes */
int _atoi(char *s); /* numbo.c */
int _isalpha(int c); /* alphabeat.c */
int _separator(char c, char *separator); /* sepway.c */
int isintact(info_t *info); /* shocked.c */
int _strlen(const char *s); /* shorty.c */
int _strcmp(char *s1, char *s2); /* strumming.c */
char *_strcat(char *dest, char *src); /* concatMeMaybe.c */
char *sub_search(const char *text, const char *substr); /* sublove.c */
char *_strcpy(char *dest, char *src); /* copycat.c */
char *_strdup(const char *text); /* magic.c */
void _puts(char *); /* bohemRhapsody.c */
int _putchar(char c);
list_t *add_node(list_t **head, const char *text, int len); /* addict.c */
list_t *add_node_end(list_t **head, const char *text);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t *head);
size_t list_len(const list_t *h);
ssize_t get_node_index(list_t *head, list_t *node);
list_t *find_node_with_prefix(list_t *head, char *prefix, char next_char);
size_t print_linked_list(const list_t *head);
char **convert_list_to_strings(list_t *head);
size_t list_length(const list_t *head);


#endif
