#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <stddef.h>

/**
	* struct shell_ctx - holds shell state
	* @env: environment variables
	* @last_status: last command exit status
	* @should_exit: flag to signal shell termination
	*/
typedef struct shell_ctx
{
	char **env;
	int last_status;
	int exit_status;
	int should_exit;
} shell_ctx_t;

extern char **environ;
char **split_line(char *line);
void free_tokens(char **tokens);
int handle_builtin(shell_ctx_t *ctx, char **args);
char *find_command(char *cmd, shell_ctx_t *ctx);
void execute_command(char **argv, char **env);
ssize_t _my_getline(char **lineptr, size_t *n);
char **split_line(char *line);
void free_tokens(char **tokens);
#endif
