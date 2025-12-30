#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "getline.h"

#define BUF_SIZE 1024
extern char **environ;

/**
	* struct shell_ctx - Shell state context
	* @exit_status: Last command exit status
	* @should_exit: Exit flag
	* @env: Environment variables
	*/
typedef struct shell_ctx
{
	int exit_status;
	int should_exit;
	char **env;
} shell_ctx_t;

/* Prototypes */
void execute_command(char **argv, shell_ctx_t *ctx);
char *get_path_value(char **env);
char *find_path(char *command, char **env);
int handle_builtin(char **argv, shell_ctx_t *ctx);

#endif
