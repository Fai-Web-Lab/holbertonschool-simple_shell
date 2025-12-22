#include "shell.h"

/**
	* run_shell - main shell loop
	* @prog_name: program name
	*
	* Return: Nothing
	*/
void run_shell(char *prog_name)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "#cisfun$ ", 9);

	read = getline(&line, &len, stdin);
	if (read == -1)
	break;

	if (!is_only_spaces(line))
	execute_command(line, prog_name);
	}
	free(line);
}
