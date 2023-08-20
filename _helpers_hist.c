#include "main.h"
/**
 * get_history_file - gets the history file
 * @options: Struct contains all command options
 * Return: string containg history file
 */
char *get_history_file(options_t *options)
{
	char *buffer, *dir;

	dir = _getenv(options, "HOME=");
	if (!dir)
	{
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(HISTORY_FILE) + 2));
	if (!buffer)
	{
		return (NULL);
	}
	buffer[0] = 0;
	_strcpy(buffer, dir);
	_strcat(buffer, "/");
	_strcat(buffer, HISTORY_FILE);

	return (buffer);
}

/**
 * write_history - creates of appends to a file
 * @options: Struct contains all command options
 * Return: 1 on success, otherwize  -1
 */
int write_history(options_t *options)
{
	ssize_t fd;
	char *filename = get_history_file(options);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = options->history; node; node = node->next)
	{
		_puts_fd(node->str, fd);
		_putchar_fd('\n', fd);
	}
	_putchar_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @options: Struct contains all command options
 * Return: @history_count on success, 0 otherwise
 */
int read_history(options_t *options)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(options);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			add_history_list(options, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		add_history_list(options, buf + last, linecount++);
	free(buf);
	options->history_count = linecount;
	while (options->history_count-- >= HIST_BUFFER)
		delete_node_by_index(&(options->history), 0);
	renumber_history(options);
	return (options->history_count);
}

/**
 * add_history_list - adds a history to linked list
 * @options: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount
 * Return: Always 0
 */
int add_history_list(options_t *options, char *buf, int linecount)
{
	list_t *node = NULL;

	if (options->history)
		node = options->history;
	add_node_end(&node, buf, linecount);

	if (!options->history)
		options->history = node;
	return (0);
}

/**
 * renumber_history - renumbers history linked list after changes
 * @options: Structure containing potential arguments. Used to maintain
 * Return: @history_count
 */
int renumber_history(options_t *options)
{
	list_t *node = options->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (options->history_count = i);
}
