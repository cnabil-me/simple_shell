#include "main.h"
/**
 * exit_shell - exits the shell
 * @options: Struct contains all command options
 * Return: exit status
 */
int exit_shell(options_t *options)
{
	int exit_status;

	if (options->argv[1])
	{
		exit_status = _atoi_w_err(options->argv[1]);
		if (exit_status == -1)
		{
			options->return_status = 2;
			print_error(options, "Illegal number: ");
			_puts_err(options->argv[1]);
			_putchar_err('\n');
			return (EXIT_FAILURE);
		}
		options->err_no = _atoi_w_err(options->argv[1]);
		return (-2);
	}
	options->err_no = -1;
	return (-2);
}

/**
 * _cd - changes the current directory of the process
 * @options: Struct contains all command options
 * Return: 0 on success otherways returns 1
 */
int _cd(options_t *options)
{
	char *str, *dir, buffer[R_BUF_SIZE];
	int chdir_ret;

	str = getcwd(buffer, R_BUF_SIZE);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!options->argv[1])
	{
		dir = _getenv(options, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
			    chdir((dir = _getenv(options, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(options->argv[1], "-") == 0)
	{
		if (!_getenv(options, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(options, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
		    chdir((dir = _getenv(options, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(options->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(options, "can't cd to ");
		_puts_err(options->argv[1]), _putchar_err('\n');
	}
	else
	{
		_setenv(options, "OLDPWD", _getenv(options, "PWD="));
		_setenv(options, "PWD", getcwd(buffer, R_BUF_SIZE));
	}
	return (EXIT_SUCCESS);
}

/**
 * _help - show help manual
 * @options: Struct contains all command options
 * Return: Always 0
 */
int _help(options_t *options)
{

	char **arg_arr;

	arg_arr = options->argv;
	(void)arg_arr;
	_puts("help call works. Function not implemented yet  \n");

	return (EXIT_SUCCESS);
}
/**
 * _hist - displays the history list
 * @options: Struct contains all command options
 *  Return: Always 0
 */
int _hist(options_t *options)
{
	print_list(options->history);
	return (EXIT_SUCCESS);
}
