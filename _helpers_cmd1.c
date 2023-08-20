#include "main.h"
/**
 * input_buf - the buffers chained commands
 * @options: struct contains all command options
 * @buf: buffer address
 * @len: len var address
 * Return: @int bytes read
 */
ssize_t input_buf(options_t *options, char **buf, size_t *len)
{
	ssize_t read = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sig_handler);
		read = _getline(options, buf, &len_p);

		if (read > 0)
		{
			if ((*buf)[read - 1] == '\n')
			{
				(*buf)[read - 1] = '\0';
				read--;
			}
			options->line_flag_count = 1;
			delete_comments(*buf);
			add_history_list(options, *buf, options->history_count++);
			{
				*len = read;
				options->cmd_buffer = buf;
			}
		}
	}
	return (read);
}

/**
 * get_input - gets a line minus the newline
 * @options: struct contains all command options
 * Return: bytes read
 */
ssize_t get_input(options_t *options)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t read = 0;
	char **buf_p = &(options->arg), *p;

	_putchar(BUF_FLUSH);
	read = input_buf(options, &buf, &len);
	if (read == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain_status(options, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain_delimiter(options, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			options->cmd_type = DEFULT_CMD;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (read);
}

/**
 * read_buf - read buffer
 * @options: struct contains all command options
 * @buf: buffer
 * @size: size
 * Return: rad buffer byts
 */
ssize_t read_buf(options_t *options, char *buf, size_t *size)
{
	ssize_t read_b = 0;

	if (*size)
	{
		return (0);
	}
	read_b = read(options->read_fd, buf, R_BUF_SIZE);
	if (read_b >= 0)
	{
		*size = read_b;
	}
	return (read_b);
}

/**
 * _getline - memic of getline
 * @options: struct contains all command options
 * @ptr:pointer to buffer
 * @length: preallocated ptr buffer size
 * Return: @str
 */
int _getline(options_t *options, char **ptr, size_t *length)
{
	static char buf[R_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, str = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		str = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(options, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, str, str ? str + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (str)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	str += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = str;
	*ptr = p;
	return (str);
}

/**
 * sig_handler - disable ctrl-C
 * @sig_num: signal number
 * Return: void
 */
void sig_handler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
