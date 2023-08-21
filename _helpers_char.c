#include "main.h"

/**
 * _putchar - writes the character to stdout
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char ch)
{
	static int i;
	static char buf[W_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= W_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
	{
		buf[i++] = ch;
	}

	return (1);
}

/**
 * is_delim - checks if char is delimeter
 * @c: char to check
 * @delim: delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @path: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to the new buffer
 */
char *dup_chars(char *path, int start, int stop)
{
	static char buffer[R_BUF_SIZE];
	int i = 0;
	int j = 0;

	for (j = 0, i = start; i < stop; i++)
	{
		if (path[i] != ':')
		{
			buffer[j++] = path[i];
		}
	}
	buffer[j] = 0;
	return (buffer);
}

/**
 *_isalpha - checks if alphabetic
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * _putchar_fd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar_fd(char c, int fd)
{
	static int i;
	static char buf[W_BUF_SIZE];

	if (c == BUF_FLUSH || i >= W_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
