#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <stddef.h>

/**
	* struct shell_ctx - context for shell state
	* @env: environment variables
	* @should_exit: flag to exit shell
	* @exit_status: last exit status
	*/
typedef struct shell_ctx
{
	char **env;
	int should_exit;
	int exit_status;
} shell_ctx_t;

extern char **environ;
char **split_line(char *line);
void free_tokens(char **tokens);
int handle_builtin(shell_ctx_t *ctx, char **args);
char *find_command(char *cmd, shell_ctx_t *ctx);
void execute_command(shell_ctx_t *ctx, char **argv, char **env);
ssize_t _my_getline(char **lineptr, size_t *n);
char **split_line(char *line);
void free_tokens(char **tokens);
int _atoi(char *s);
int is_number(char *s);
int handle_exit_error(char *arg);
/**
	* copy_token - copy substring into new allocated buffer
	* @line: input line
	* @start: start index
	* @len: length of token
	* Return: pointer to new token
	*/
char *copy_token(char *line, int start, int len);

#endif
