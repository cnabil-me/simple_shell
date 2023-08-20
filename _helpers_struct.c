#include "main.h"
/**
 * clear_options - initializes @options_t
 * @options: Struct contains all command options
 * Return: void
 */
void clear_options(options_t *options)
{
	options->argc = 0;
	options->path = NULL;
	options->arg = NULL;
	options->argv = NULL;
}

/**
 * set_options - set options @options_t
 * @options: Struct contains all command options
 * @av: argument vector
 */
void set_options(options_t *options, char **av)
{
	int i = 0;

	options->filename = av[0];
	if (options->arg)
	{
		options->argv = strtow(options->arg, " \t");
		if (!options->argv)
		{

			options->argv = malloc(sizeof(char *) * 2);
			if (options->argv)
			{
				options->argv[0] = _strdup(options->arg);
				options->argv[1] = NULL;
			}
		}
		for (i = 0; options->argv && options->argv[i]; i++)
			;
		options->argc = i;

		replace_alias(options);
		replace_to(options);
	}
}

/**
 * free_options - frees @options_t
 * @options: Struct contains all command options
 * @is_all: true if  all fields
 */
void free_options(options_t *options, int is_all)
{
	ffree(options->argv);
	options->argv = NULL;
	options->path = NULL;
	if (is_all)
	{
		if (!options->cmd_buffer)
			free(options->arg);
		if (options->env)
			free_list(&(options->env));
		if (options->history)
			free_list(&(options->history));
		if (options->alias)
			free_list(&(options->alias));
		ffree(options->environ);
		options->environ = NULL;
		_bfree((void **)options->cmd_buffer);
		if (options->read_fd > 2)
			close(options->read_fd);
		_putchar(BUF_FLUSH);
	}
}
