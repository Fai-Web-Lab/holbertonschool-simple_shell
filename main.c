#include "shell.h"

/**
	* main - Entry point for the shell
	* @argc: Argument count (unused)
	* @argv: Argument vector (program name)
	*
	* Return: 0 on success
	*/
int main(int argc, char **argv)
{
	(void)argc;
	run_shell(argv[0]);
	return (0);
}
