#ifndef _STRUCTS_
#define _STRUCTS_

/**
 * struct list_str -  linked list
 * @num: number field
 * @str: string field
 * @next: next node
 */
typedef struct list_str
{
	int num;
	char *str;
	struct list_str *next;
} list_t;

/**
 *struct passinfo -  Struct contains all command options
 *@arg: _getline string containing all arguements
 *@argv: arg array of strings
 *@path: current command path
 *@argc: arguments count
 *@line_length: line length
 *@err_no: exit  error number
 *@line_flag_count: input count line
 *@filename: program filename
 *@env: local env linked list
 *@environ: local environ from LL env
 *@history: history node
 *@alias:  alias node
 *@is_env_changed: check if env was changed
 *@return_status: return status of last exec cmd
 *@cmd_buffer: commande buffer pointer
 *@cmd_type: || -  && - , -  ;
 *@read_fd: readed file descriptor
 *@history_count: history line count
 *@command_options - the command options for the program
 */
typedef struct command_options
{
	int argc;
	char *arg;
	char **argv;
	char *path;
	unsigned int line_length;
	int err_no;
	int line_flag_count;
	char *filename;
	char **environ;
	int is_env_changed;
	int return_status;
	char **cmd_buffer;
	int cmd_type;
	int read_fd;
	int history_count;
	list_t *env;
	list_t *history;
	list_t *alias;

} options_t;

/**
 *struct builtin - map of built in cmd name and according function
 *@name:  builtin cmd name
 *@fn: according function
 */
typedef struct builtin
{
	char *name;
	int (*fn)(options_t *);

} builtin_table;

#endif
