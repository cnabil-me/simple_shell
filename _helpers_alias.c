#include "main.h"
/**
 * unset_alias - unset an alias
 * @options: Struct contains all command options
 * @str: alias string
 * Return: 0 on success, 1 on error
 */
int unset_alias(options_t *options, char *str)
{
	char c;
	char *ptr;
	int status;

	ptr = _strchr(str, '=');
	if (!ptr)
	{
		return (EXIT_FAILURE);
	}
	c = *ptr;
	*ptr = 0;
	status = delete_node_by_index(&(options->alias),
				      get_index_of_node(options->alias,
							find_node_starts_with(options->alias, str, -1)));
	*ptr = c;
	return (status);
}

/**
 * set_alias - sets alias
 * @options: Struct contains all command options
 * @str: the string alias
 * Return: 0 on success, 1 on error
 */
int set_alias(options_t *options, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(options, str));

	unset_alias(options, str);
	return (add_node_end(&(options->alias), str, 0) == NULL);
}

/**
 * echo_alias - prints an alias string
 * @node: alias node
 * Return: 0 on success, 1 on error
 */
int echo_alias(list_t *node)
{
	char *ptr = NULL;
	char *alias = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (alias = node->str; alias <= ptr; alias++)
		{
			_putchar(*alias);
		}
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/**
 * _alias - display aliases
 * @options: struct contains all command options
 * Return: Always 0
 */
int _alias(options_t *options)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (options->argc == 1)
	{
		node = options->alias;
		while (node)
		{
			echo_alias(node);
			node = node->next;
		}
		return (EXIT_SUCCESS);
	}
	for (i = 1; options->argv[i]; i++)
	{
		p = _strchr(options->argv[i], '=');
		if (p)
		{
			set_alias(options, options->argv[i]);
		}
		else
		{
			echo_alias(find_node_starts_with(options->alias, options->argv[i], '='));
		}
	}

	return (EXIT_SUCCESS);
}
/**
 * replace_alias - replaces an aliases in the tokenized string
 * @options: struct contains all command options
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(options_t *options)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = find_node_starts_with(options->alias, options->argv[0], '=');
		if (!node)
			return (0);
		free(options->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		options->argv[0] = p;
	}
	return (1);
}
