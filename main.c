#include "shell.h"
#include "getline.h"
#include <unistd.h>
#include <stdlib.h>

/**
<<<<<<< HEAD
	* main - Entry point of the shell
	* @ac: argument count (unused)
	* @av: argument vector (unused)
	* @env: environment variables
=======
	* main - entry point of shell
>>>>>>> 6c97ab6 (working on advanced 9: simple shell 0.1.1)
	*
	* Return: 0
	*/

int main(int ac, char **av, char **env)
{
<<<<<<< HEAD
	char *line = NULL;
	size_t len = 0;
	char **argv;

	(void)ac;
	(void)av;

	while (1)
	{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);


	if (_getline(&line, &len) == -1)
	break;

	argv = split_line(line);

	execute_command(argv, env);

	free_tokens(argv);
=======
	char *line;
	size_t len;
	ssize_t read;

	line = NULL;
	len = 0;

	while (1)
	{
	print_prompt();
	read = _getline(&line, &len, STDIN_FILENO);
	if (read == -1)
	{
	break;
	}

	line[read - 1] = '\0';
	if (*line)
	{
	execute_command(line, NULL);
	}
>>>>>>> 6c97ab6 (working on advanced 9: simple shell 0.1.1)
	}

	free(line);
	return (0);
}
