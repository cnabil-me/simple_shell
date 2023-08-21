#include "main.h"
/**
 * handle_cmds - handle the commande
 * @options: Struct contains all command options
 * @av: the argument vector
 * Return: 0 on success, 1 on error
 */
int handle_cmds(options_t *options, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_options(options);
		if (interactive(options))
			_puts("$ ");
		_putchar_err(BUF_FLUSH);
		r = get_input(options);
		if (r != -1)
		{
			set_options(options, av);
			builtin_ret = handle_builtin_cmd(options);
			if (builtin_ret == -1)
				handle_extern_cmd(options);
		}
		else if (interactive(options))
			_putchar('\n');
		free_options(options, 0);
	}
	write_history(options);
	free_options(options, 1);
	if (!interactive(options) && options->return_status)
		exit(options->return_status);
	if (builtin_ret == -2)
	{
		if (options->err_no == -1)
			exit(options->return_status);
		exit(options->err_no);
	}
	return (builtin_ret);
}

/**
 * handle_builtin_cmd - finds a builtin command
 * @options: Struct contains all command options
 * Return: -1: builtin not found,
 *	    0: builtin executed successfully,
 *	    1: builtin executed unsuccessful,
 *	   -2: builtin signals exit
 */
int handle_builtin_cmd(options_t *options)
{
	int i, built_in_ret = -1;
	builtin_table builtins[] = {
	    {"exit", exit_shell},
	    {"alias", _alias},
	    {"cd", _cd},
	    {"env", _env},
	    {"setenv", hsh_setenv},
	    {"unsetenv", hsh_unsetenv},
	    {"history", _hist},
	    {"help", _help},
	    {NULL, NULL}};

	for (i = 0; builtins[i].name; i++)
		if (_strcmp(options->argv[0], builtins[i].name) == 0)
		{
			options->line_length++;
			built_in_ret = builtins[i].fn(options);
			break;
		}
	return (built_in_ret);
}
/**
 * handle_extern_cmd - finds a command in PATH
 * @options: Struct contains all command options
 * Return: void
 */
void handle_extern_cmd(options_t *options)
{
	char *path = NULL;
	int i, k;

	options->path = options->argv[0];
	if (options->line_flag_count == 1)
	{
		options->line_length++;
		options->line_flag_count = 0;
	}
	for (i = 0, k = 0; options->arg[i]; i++)
		if (!is_delim(options->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = find_cmd_path(options, _getenv(options, "PATH="), options->argv[0]);
	if (path)
	{
		options->path = path;
		fork_cmd(options);
	}
	else
	{
		if ((interactive(options) || _getenv(options, "PATH=") || options->argv[0][0] == '/') && is_exec(options, options->argv[0]))
			fork_cmd(options);
		else if (*(options->arg) != '\n')
		{
			options->return_status = 127;
			print_error(options, "not found\n");
		}
	}
}
/**
 * fork_cmd - forks a an exec thread to run cmd
 * @options: Struct contains all command options
 * Return: void
 */
void fork_cmd(options_t *options)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(options->path, options->argv, get_environ(options)) == -1)
		{
			free_options(options, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(options->return_status));
		if (WIFEXITED(options->return_status))
		{
			options->return_status = WEXITSTATUS(options->return_status);
			if (options->return_status == 126)
				print_error(options, "Permission denied\n");
		}
	}
}
/**
 * interactive - cheks if shell is in interactive mode
 * @options: Struct contains all command options
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(options_t *options)
{
	return (isatty(STDIN_FILENO) && options->read_fd <= 2);
}
