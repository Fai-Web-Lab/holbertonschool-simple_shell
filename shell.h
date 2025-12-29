#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <stddef.h>
#include <unistd.h>

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
int builtin_setenv(shell_ctx_t *ctx, char **args);
int builtin_unsetenv(shell_ctx_t *ctx, char **args);
char *build_env_var(char *name, char *value);
int find_env_index(char **env, char *name);
char **copy_env(char **env);
int builtin_env(shell_ctx_t *ctx);
#endif
