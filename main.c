#include "shell.h"

/**
	* main - Entry point for the simple shell
	* @argc: Argument count (unused)
	* @argv: Argument vector (used for shell program name)
	* Return: 0 on success, 1 on failure
	*/
int main(int argc, char **argv)
{
	(void)argc;
	run_shell(argv[0]);
	return (0);
}
