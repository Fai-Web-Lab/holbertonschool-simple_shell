#include "shell.h"

/**
 * main - Entry point of the simple shell
 * @ac: Argument count (unused)
 * @av: Argument vector, used to get the program name
 *
 * Description:
 * Initializes the shell and starts its main execution loop.
 * The exit status of the shell matches the status of the last
 * executed command, ensuring proper behavior in non-interactive mode.
 *
 * Return: Exit status of the last executed command
 */
int main(int ac, char **av)
{
	int status;

	(void)ac;

	status = run_shell(av[0]);
	return (status);
}
