#include "main.h"
/**
 * **strtow - splits a string into words (repeat delimiters are ignored)
 * @str: input string
 * @d: delimeter string
 * Return: pointer array of strings or NULL
 */
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * replace_to - replaces to the tokenized string
 * @options: struct contains all command options
 * Return: 1 on success, 0 otherwise
 */
int replace_to(options_t *options)
{
	int i = 0;
	list_t *node;

	for (i = 0; options->argv[i]; i++)
	{
		if (options->argv[i][0] != '$' || !options->argv[i][1])
			continue;

		if (!_strcmp(options->argv[i], "$?"))
		{
			replace_string(&(options->argv[i]),
				       _strdup(convert_digit(options->return_status, 10, 0)));
			continue;
		}
		if (!_strcmp(options->argv[i], "$$"))
		{
			replace_string(&(options->argv[i]),
				       _strdup(convert_digit(getpid(), 10, 0)));
			continue;
		}
		node = find_node_starts_with(options->env, &options->argv[i][1], '=');
		if (node)
		{
			replace_string(&(options->argv[i]),
				       _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&options->argv[i], _strdup(""));
	}
	return (0);
}
