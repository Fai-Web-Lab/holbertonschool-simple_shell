#include "shell.h"
#include "getline.h"

/**
	* main - shell entry point
	*
	* Return: 0
	*/
int main(void)
{
	char *line;
	size_t len;
	ssize_t read;
	char *args[2];

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
	args[0] = line;
	args[1] = NULL;

	if (*line)
	{
	execute_command(line, args);
	}
	}

	free(line);
	return (0);
}
