#include "shell.h"

/**
	* main - Entry point for the simple shell
	* Return: The exit status of the shell
	*/
int main(void)
{
	char *line = NULL, *token, *argv[64];
	size_t n = 0;
	int i;
	shell_ctx_t ctx;

	ctx.exit_status = 0;
	ctx.should_exit = 0;
	ctx.env = environ;

	while (!ctx.should_exit)
	{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "#cisfun$ ", 9);

	if (_getline(&line, &n, STDIN_FILENO) == -1)
	break;

	for (i = 0; line[i]; i++)
	{
	if (line[i] == '\n')
	line[i] = '\0';
	}

	i = 0;
	token = _strtok(line, " \t");
	while (token && i < 63)
	{
	argv[i++] = token;
	token = _strtok(NULL, " \t");
	}
	argv[i] = NULL;

	if (argv[0] != NULL)
	{
	if (!handle_builtin(argv, &ctx))
	execute_command(argv, &ctx);
	}
	}
	free(line);
	return (ctx.exit_status);
}
