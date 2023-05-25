#ifndef SHELL_H
#define SHELL_H

#define MAX_ARGS 64
#define BUFFER 1024 /* define constant buffer of 1024 bytes */
#define WRITE_BUFFER 1024
#define READ_BUFFER 1024
#define BUFFER_FLUSHER -1
#define CONVERT_UNSIGNED 2
#define CONVERT_LOWERCASE 1
#define ARCO_FILE ".simple_shell_history"
#define ARCO_MAX 4096
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
#define USE_GETLINE 0
#define USE_STRTOK 0

/* Library Used */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <error.h>
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
 * struct cmd_info - contains arguments to be passed into a function
 * @argv: an array of strings containing the command arguments
 * @readFd: the file descriptor from which to read line input
 * @lineCntFlag: set to 1 to lineCnt this line of input
 * @history: the history linked list node
 * @path: the path of the current command
 * @environs: custom modified copy of the env variables from the linked list env
 * @arg: a string containing the command arguments generated from getline
 * @lineCnt: the line lineCnt of the input
 * @alias: the alias linked list node
 * @envChanged: set to 1 if the environment variables were modified
 * @cmdBufType: the type of command buffer: CMD_type ||, &&, ;
 * @env: the linked list containing the local copy of the environment variables
 * @cmdBuf: a pointer to the command ; chain buffer, used for memory management
 * @status: the return status of the last executed command
 * @argc: the argument lineCnt
 * @fname: the filename of the program
 * @errNum: the error code for exit() calls
 * @histCount: the history line number lineCnt
 * @line_count: history of number lineCnt
 */
typedef struct cmd_info
{
	char **argv;
	int readFd;
	unsigned int line_count;
	int lineCntFlag;
	list_t *history;
	char *path;
	char **environs;
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

#define INFORMED_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/*
 * Description: Header file for prototypes in Shell Project
 */

/* Prototypes */
int _atoi(char *s);
int _isalpha(int c);
int _separator(char c, char *separator);
int isintact(info_t *info);
int _strlen(const char *s);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *sub_search(const char *text, const char *substr);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *text);
void _puts(char *);
int _putchar(char);
char *starts_with(const char *, const char *);
void _eputs(char *blop);
int samo(char *h);
void _eputs(char *);
int _print_d(int, int);
int _eputchar(char n);
void leap_samo(info_t *skip, char *jazz);
int _print_d(int ima, int less);
char *starts_with(const char *amfm, const char *copper);
char *convert_number(long int num, int crackle, int snap);
void gene(char *lineCnt);
list_t *add_node(list_t **head, const char *text, int len);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head);
size_t list_len(const list_t *h);
ssize_t get_node_index(list_t *head, list_t *node);
list_t *find_node_with_prefix(list_t *head, char *prefix, char next_char);
size_t print_linked_list(const list_t *head);
char **convert_list_to_strings(list_t *head);
size_t list_length(const list_t *head);
int wickham(info_t *data);
char *arco_iris(info_t *data);
int planet_giza(info_t *data);
int pandemia(info_t *data, char *path, int lineCnt);
int dinaledi(info_t *data);
int oxford_circus(info_t *data);
char *mndsgn(info_t *data, const char *text);
int sibali(info_t *data);
int carluccio(info_t *data);
int coogie(info_t *data);
char **fjord(info_t *data);
int dunia(info_t *data, char *var);
int ottolenghi(info_t *data, char *var, char *num);
int shelly(info_t *data, char **av);
int konke(info_t *data);
void casa_cmd(info_t *data);
void joachim_fork(info_t *data);
int avenue(info_t *data);
int behbeh(info_t *data, char *str);
int sondela(info_t *data, char *str);
int percolator(list_t *list);
int monaco(info_t *data);
char *_strncpy(char *dtsin, char *locat, int n);
char *_strncat(char *dtsin, char *locat, int n);
char *_strchr(char *s, char c);
int my_deli(char c, char *limiter);
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);
char *_memset(char *s, char b, unsigned int n);
void ffreed(char **leave);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int aliaslace(info_t *info);
int vatspa(info_t *info);
int stringing(char **old, char *new);
int bfree(void **pir);
int is_cmd(info_t *data, char *path);
char *dup_chars(char *pathtxt, int begin, int end);
char *find_path(info_t *data, char *pathtxt, char *cmd);

#endif