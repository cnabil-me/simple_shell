#ifndef _MAIN_H
#define _MAIN_H

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
#include "structs.h"

/* CMD DETECTOR */
#define DEFULT_CMD 0
#define OR_CMD 1
#define AND_CMD 2
#define CHAIN_CMD 3

/* BUFFERS */
#define R_BUF_SIZE 1024
#define W_BUF_SIZE 1024
#define HIST_BUFFER 4096
#define BUF_FLUSH -1

/* INT INDICATORS*/
#define LOWERCASE 1
#define UNSIGNED 2

/* HISTORY FILE LOCATION */
#define HISTORY_FILE ".hsh_history"

/* GLOBAL ENV VARIABLE */
extern char **environ;

/* BUILT IN FUNCTIONS */
int exit_shell(options_t *);
int _cd(options_t *);
int _help(options_t *);
int _hist(options_t *);

/* ALIASES */
int _alias(options_t *options);
int echo_alias(list_t *node);
int set_alias(options_t *options, char *str);
int unset_alias(options_t *options, char *str);
int replace_alias(options_t *);

/* CHAINS */
int is_chain_delimiter(options_t *, char *, size_t *);
void check_chain_status(options_t *, char *, size_t *, size_t, size_t);

/* DIGIT FUNCTIONS HELPERS */
int _atoi(char *s);

/* CHARACTER FUNCTIONS HELPERS */
int is_delim(char, char *);
int _isalpha(int);
int _putchar(char);
char *dup_chars(char *, int, int);
int _putchar_fd(char c, int fd);

/* COMMANDS FUNCTIONS HELPERS */
ssize_t input_buf(options_t *options, char **buf, size_t *len);
ssize_t get_input(options_t *options);
ssize_t read_buf(options_t *options, char *buf, size_t *size);
ssize_t get_input(options_t *);
int _getline(options_t *, char **, size_t *);
void sig_handler(int);
int is_exec(options_t *, char *);
char *find_cmd_path(options_t *, char *, char *);
void delete_comments(char *);

/* DIGITS FUNCTIONS HELPERS */
int _atoi(char *);
int _atoi_w_err(char *);
char *convert_digit(long int, int, int);
int print_decimal(int input, int fd);

/* ENV FUNCTIONS HELPERS */
int _env(options_t *);
char *_getenv(options_t *, const char *);
int hsh_setenv(options_t *);
int hsh_unsetenv(options_t *);
int init_env_list(options_t *);
char **get_environ(options_t *);
int _unsetenv(options_t *, char *);
int _setenv(options_t *, char *, char *);

/* ERRORS FUNCTIONS HELPERS */
void print_error(options_t *, char *);
void _puts_err(char *);
int _putchar_err(char);

/* HISTORY FUNCTIONS HELPERS */
char *get_history_file(options_t *options);
int read_history(options_t *options);
int add_history_list(options_t *options, char *buf, int linecount);
int write_history(options_t *options);
int renumber_history(options_t *options);

/* LISTS FUNCTIONS HELPERS */
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_by_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *find_node_starts_with(list_t *, char *, char);
ssize_t get_index_of_node(list_t *, list_t *);

/* MEMORY FUNCTIONS HELPERS */
int _bfree(void **);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* STRUCTURES FUNCTIONS HELPERS */
void clear_options(options_t *);
void set_options(options_t *, char **);
void free_options(options_t *, int);

/* TOKENS FUNCTIONS HELPERS */
int replace_to(options_t *);
char **strtow(char *, char *);

/* STRING FUNCTIONS HELPERS */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strncpy(char *, char *, int);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
int replace_string(char **, char *);
int _puts_fd(char *str, int fd);

/* MAIN SHELL FUNCTIONS HELPERS */
int main(int ac, char **av);
int handle_cmds(options_t *, char **);
int handle_builtin_cmd(options_t *);
void handle_extern_cmd(options_t *);
void fork_cmd(options_t *);
int interactive(options_t *);

#endif
