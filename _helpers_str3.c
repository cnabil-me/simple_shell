#include "main.h"
/**
 * replace_string - replace a string
 * @old: old string
 * @new: new string
 * Return: 1 on succes,otherwise 0.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
/**
 *_puts_fd - prints filedescriptor
 * @str: string to be printed
 * @fd: filedescriptor to write to
 * Return: number of chars puts
 */
int _puts_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putchar_fd(*str++, fd);
	}
	return (i);
}
