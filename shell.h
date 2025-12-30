#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

extern char **environ;

/**
	* struct shell_ctx_s - Shell context
	* @env: Environment variables
	*/
typedef struct shell_ctx_s
{
	char **env;
} shell_ctx_t;

void print_prompt(void);
int execute_command(char *cmd, char **args, char **env);
void print_error(char *cmd);
char *get_path(char *cmd, char **env);
char *copy_token(char *line, int start, int len);
char **copy_env(char **env);
int builtin_env(shell_ctx_t *ctx);
ssize_t _getline(char **lineptr, size_t *n, int fd);

#endif
