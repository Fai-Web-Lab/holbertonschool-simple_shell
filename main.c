#include "shell.h"

/**
	* main - entry point
	* @ac: argument count
	* @av: argument vector
	*
	* Return: Always 0
	*/
int main(int ac, char **av)
{
	(void)ac;

	run_shell(av[0]);
	return (0);
}
