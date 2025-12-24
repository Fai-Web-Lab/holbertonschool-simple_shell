#include "shell.h"

/**
	* run_shell - Main loop of the shell
	* @prog_name: program name (unused)
	*/
void run_shell(char *prog_name)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t nread;

	(void)prog_name;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	printf("%s", PROMPT_TEXT);

	nread = getline(&line, &n, stdin);
	if (nread == -1)
	break;

	if (nread > 1)
	execute_command(line);
	}
	free(line);
}
