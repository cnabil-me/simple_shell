#include "main.h"
/**
 * get_environ - get string array  environ
 * @options: Struct contains all command options
 * Return: array of strings arg
 */
char **get_environ(options_t *options)
{
	if (!options->environ || options->is_env_changed)
	{
		options->environ = list_to_strings(options->env);
		options->is_env_changed = 0;
	}

	return (options->environ);
}

/**
 * _unsetenv - Remove env variable
 * @options: Struct contains all command options
 * @var:  string env var property
 * Return: 1 if unset success, otherwise 0
 */
int _unsetenv(options_t *options, char *var)
{
	list_t *node = options->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (EXIT_SUCCESS);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			options->is_env_changed = delete_node_by_index(&(options->env), i);
			i = 0;
			node = options->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (options->is_env_changed);
}
/**
 * _setenv - Initialize a new environment variable,
 * @options: Struct contains all command options
 * @var: string env var property
 * @value: string env var value
 * Return: Always 0
 */
int _setenv(options_t *options, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = options->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			options->is_env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(options->env), buf, 0);
	free(buf);
	options->is_env_changed = 1;
	return (EXIT_SUCCESS);
}
