#include "shell.h"
#include <signal.h>

/**
	* handle_sigint - Signal handler for Ctrl+C
	* @sig: Signal number
	*/
void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}

/**
	* main - Entry point
	* Return: Exit status
	*/
int main(void)
{
	char *line = NULL, *token, *argv[64];
	size_t n = 0;
	int i;
	shell_ctx_t ctx;

	ctx.exit_status = 0;
	ctx.should_exit = 0;
	ctx.env = copy_env();
	signal(SIGINT, handle_sigint);
	while (!ctx.should_exit)
	{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "#cisfun$ ", 9);
	if (_getline(&line, &n, STDIN_FILENO) == -1)
	break;
	for (i = 0; line[i]; i++)
	if (line[i] == '\n')
	line[i] = '\0';
	i = 0;
	token = _strtok(line, " \t");
	while (token && i < 63)
	{
	argv[i++] = token;
	token = _strtok(NULL, " \t");
	}
	argv[i] = NULL;
	if (argv[0] != NULL && !handle_builtin(argv, &ctx))
	execute_command(argv, &ctx);
	}
	for (i = 0; ctx.env[i]; i++)
	free(ctx.env[i]);
	free(ctx.env);
	free(line);
	return (ctx.exit_status);
}
