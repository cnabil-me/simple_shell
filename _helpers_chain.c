#include "main.h"
/**
 * check_chain_status - checks chaining based on last status
 * @options: struct contains all command options
 * @buf: char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buffer
 * Return: Void
 */
void check_chain_status(options_t *options,
			char *buf, size_t *p,
			size_t i, size_t len)
{
	size_t j = *p;

	if (options->cmd_type == AND_CMD)
	{
		if (options->return_status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (options->cmd_type == OR_CMD)
	{
		if (!options->return_status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * is_chain_delimiter - check char in buffer is delimeter
 * @options: struct contains all command options
 * @buf: the char buffer
 * @p: current position address
 * Return: 1 if is a chain delimeter, 0 if not
 */
int is_chain_delimiter(options_t *options, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		options->cmd_type = OR_CMD;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		options->cmd_type = AND_CMD;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		options->cmd_type = CHAIN_CMD;
	}
	else
		return (0);
	*p = j;
	return (1);
}
