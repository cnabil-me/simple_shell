#include "main.h"
/**
 * _env - prints current environment variables
 * @options: Struct contains all command options
 * Return: Always 0
 */
int _env(options_t *options)
{
	print_list_str(options->env);
	return (EXIT_SUCCESS);
}

/**
 * _getenv - gets value single env variable
 * @options: Struct contains all command options
 * @name: env var name
 * Return: the value
 */
char *_getenv(options_t *options, const char *name)
{
	list_t *node = options->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
		{
			return (p);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * hsh_setenv - Initialize a new environment variable,
 * @options: Struct contains all command options
 * Return: Always 0
 */
int hsh_setenv(options_t *options)
{
	if (options->argc != 3)
	{
		_puts_err("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(options, options->argv[1], options->argv[2]))
	{
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/**
 * hsh_unsetenv - Remove an environment variable
 * @options: Struct contains all command options
 * Return: Always 0
 */
int hsh_unsetenv(options_t *options)
{
	int i;

	if (options->argc == 1)
	{
		_puts_err("Too few arguements.\n");
		return (EXIT_FAILURE);
	}
	for (i = 1; i <= options->argc; i++)
		_unsetenv(options, options->argv[i]);

	return (EXIT_SUCCESS);
}

/**
 * init_env_list - init env to linked list
 * @options: Struct contains all command options
 * Return: Always 0
 */
int init_env_list(options_t *options)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	options->env = node;
	return (EXIT_SUCCESS);
}
