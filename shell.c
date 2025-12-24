#include "shell.h"

/**
 * run_shell - Executes the main loop of the simple shell
 * @prog_name: Name of the shell program
 *
 * Description:
 * Displays the prompt in interactive mode, reads user input,
 * counts executed commands, and executes valid commands.
 *
 * Return: Exit status of the last executed command
 */
int run_shell(char *prog_name)
{
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t nread;
	int cmd_count = 0;
	int status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("%s", PROMPT);

		nread = getline(&lineptr, &n, stdin);
		if (nread == -1)
			break;

		if (nread > 1 && !is_only_spaces(lineptr))
		{
			cmd_count++;
			status = execute_command(lineptr, prog_name, cmd_count);
		}
	}

	free(lineptr);
	return (status);
}
/**
 * is_only_spaces - checks if a string contains only whitespace
 * @str: input string
 *
 * Return: 1 if only spaces, 0 otherwise
 */
int is_only_spaces(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
