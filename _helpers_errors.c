#include "main.h"
/**
 *_puts_err - prints string to stderr
 * @str: the string to be printed
 * Return: void
 */
void _puts_err(char *str)
{
	int i = 0;

	if (!str)
	{
		return;
	}
	while (str[i] != '\0')
	{
		_putchar_err(str[i]);
		i++;
	}
}

/**
 * _putchar_err - writes character to stderr
 * @ch: The character to print
 * Return: On success 1 otherways -1.
 */
int _putchar_err(char ch)
{
	static int i;
	static char buffer[W_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= W_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
	{
		buffer[i++] = ch;
	}
	return (1);
}

/**
 * print_error - prints an error message
 * @options: struct contains all command options
 * @str: string containing specified error type
 * Return: 0 if no numbers , converted number otherwise -1
 */
void print_error(options_t *options, char *str)
{
	_puts_err(options->filename);
	_puts_err(": ");
	print_decimal(options->line_length, STDERR_FILENO);
	_puts_err(": ");
	_puts_err(options->argv[0]);
	_puts_err(": ");
	_puts_err(str);
}
