#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUFFER 1024
#define WRITE_BUFFER 1024
#define BUFFER_FLUSHER -1
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND	2
#define CMD_CHAIN 3
#define CONVERT_LOWER 1
#define CONVERT_UNSIGNED 2
#define GETLINES 0
#define JIST_FILED	".simple_shell_history"
#define JIST_OVERFLOW	4096

extern char **environ;

/**
 * struct listNode - singly linked list
 * @num: the number field
 * @txt: a string
 * @next: points to the next list
 */
typedef struct listNode
{
	int num;
	char *txt;
	struct listNode *next;
} list_t;

/**
 *struct takeData - holds simulated arguments to pass into a function,
 *		enabling a consistent function pointer structure
 *@arg: a string got from getline with arguements
 *@line_count: the error count
 *@argv: an array of strings gotten from arg
 *@path: a string place for the right now cmf
 *@argc: the argument count
 *@digit_err: the error code value used for exit()s in shell
 *@linecount_flag: if on count this line of input, if not left alone
 *@environ: custom changed copy of environment from LL env
 *@env_changed: on if environ was changed
 *@history: the history list within the shell
 *@fname: filename, simple
 *@alias: the alias list within the current shell
 *@readingFd: the fd from which to read line input
 *@env: linked list local copy of environment of the computer
 *@worth: the return worth of the last exec'd cmd
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmdBufType: CMD_type ||, &&, ;
 *@histcount: the history line number count
 */
typedef struct takeData
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int digit_err;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int worth;

	char **cmd_buf;
	int cmdBufType;
	int readingFd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command onOff
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int hsh(info_t *, char **);
int find_builtin(info_t *);
void lookForCmd(info_t *);
void forkingCmd(info_t *);
int isCmd(info_t *, char *);
char *duplicationJustu(char *, int, int);
char *locate_path(info_t *, char *, char *);
int roundHsh(char **);
void eputin(char *);
int eputword(char);
int putFd(char c, int fd);
int putsFdk(char *txt, int fd);
int stringLen(char *);
int _strcmps(char *, char *);
char *beginWIth(const char *, const char *);
char *strConcat(char *, char *);
char *copyString (char *, char *);
char *_strdupsd(const char *);
void putin(char *);
int _putchar(char);
char *_copyString(char *, char *, int);
char *concatenateStrings(char *, char *, int);
char *strChr(char *, char);
char **strtow(char *, char *);
char **strTowed1(char *, char);
char *fillMemory (char *, char, unsigned int);
void freeStringArray (char **);
void *reallocateMemory(void *, unsigned int, unsigned int);
int invlove(info_t *);
int we_believe(char, char *);
int isAlphabetic(int);
int convertToInteger(char *);
int _erratoi(char *);
void display_err(info_t *, char *);
int printDD(int, int);
char *chnageNum(long int, int, int);
void vanishComments(char *);
int shellExit(info_t *);
int changeDir(info_t *);
int showHelp(info_t *);
int displayHistory(info_t *);
int mineAlias(info_t *);
ssize_t getInput(info_t *);
int getNextLine(info_t *, char **, size_t *);
void blockCtrlC(int);
void cleanData(info_t *);
void fixData(info_t *, char **);
void freeData(info_t *, int);
char *findEnv(info_t *, const char *);
int printMyEnv(info_t *);
int setEnvVar(info_t *);
int removeEnvVar(info_t *);
int filEnvList(info_t *);
char **get_environ(info_t *);
int remEnv(info_t *, char *);
int fixEnv(info_t *, char *, char *);
char *get_history_file(info_t *data);
int genHistory(info_t *data);
int cramHis(info_t *data);
int towerPisa(info_t *data, char *buffed, int linecount);
int numKimbad(info_t *data);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_finish(list_t **, const char *, int);
size_t displayList_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t displayList(const list_t *);
list_t *node_begins(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int isChainDelim(info_t *, char *, size_t *);
void validateChain(info_t *, char *, size_t *, size_t, size_t);
int substituteAlias (info_t *);
int substituteVar(info_t *);
int substituteString(char **, char *);

#endif