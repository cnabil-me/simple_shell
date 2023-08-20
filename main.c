#include "main.h"
#include "structs.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	options_t options[] = {{0, NULL, NULL,
			     0, 0, 0, 0, NULL, NULL, 0,
			     0, NULL, 0, 0, 0, 0, 0, 0}};
	int fd = 2;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_puts_err(av[0]);
				_puts_err(": 0: Can't open ");
				_puts_err(av[1]);
				_putchar_err('\n');
				_putchar_err(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		options->read_fd = fd;
	}
	init_env_list(options);
	read_history(options);
	handle_cmds(options, av);
	return (EXIT_SUCCESS);
}
