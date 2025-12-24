#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>

/**
	* struct shell_ctx - shell context
	* @last_status: last command exit status
	* @env: environment variables
	*/
typedef struct shell_ctx
{
	int last_status;
	char **env;
} shell_ctx_t;

extern char **environ;

void shell_loop(shell_ctx_t *ctx);
void execute_command(shell_ctx_t *ctx, char *line);
char *find_command(char *cmd, shell_ctx_t *ctx);
char **split_line(char *line);
void free_tokens(char **tokens);
void free_ctx(shell_ctx_t *ctx);

#endif
