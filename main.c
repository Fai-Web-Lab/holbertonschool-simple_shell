#include "shell.h"

/**
	* main - Entry point
	* @argc: argument count
	* @argv: argument vector
	*
	* Return: 0
	*/
int main(int argc, char **argv)
{
	(void)argc;

	run_shell(argv[0]);
	return (0);
}
