#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
<<<<<<< HEAD
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
void execute_command(char **argv, char **env);
ssize_t _my_getline(char **lineptr, size_t *n);
char **split_line(char *line);
void free_tokens(char **tokens);

/**
	* copy_token - copy substring into new allocated buffer
	* @line: input line
	* @start: start index
	* @len: length of token
	* Return: pointer to new token
	*/
char *copy_token(char *line, int start, int len);
=======
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

void print_prompt(void);
int execute_command(char *cmd, char **args);
void print_error(char *cmd);
>>>>>>> 6c97ab6 (working on advanced 9: simple shell 0.1.1)

#endif
