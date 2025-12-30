#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
<<<<<<< HEAD
<<<<<<< HEAD
	* main - Entry point of the shell
	* @ac: argument count (unused)
	* @av: argument vector (unused)
	* @env: environment variables
=======
	* main - entry point of shell
>>>>>>> 6c97ab6 (working on advanced 9: simple shell 0.1.1)
=======
	* main - Minimal shell for setenv/unsetenv
	* @ac: unused
	* @av: unused
	* @env: environment
>>>>>>> 0de24339ba50e0f0950489c943d8157701d34a98
	*
	* Return: 0
	*/
int main(int ac, char **av, char **env)
{
<<<<<<< HEAD
	char *line = NULL;
	size_t len = 0;
	char **argv;
	shell_ctx_t ctx;

	(void)ac;
	(void)av;

	ctx.env = copy_env(env);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

	if (getline(&line, &len, stdin) == -1)
	break;

	argv = split_line(line);

	if (handle_builtin(&ctx, argv))
	{
	free_tokens(argv);
	continue;
	}

	printf("Command not supported\n");
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
