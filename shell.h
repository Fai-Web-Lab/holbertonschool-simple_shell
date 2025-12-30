#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "getline.h"
#include <signal.h>

#define BUF_SIZE 1024

extern char **environ;

/**
	* struct shell_ctx - Holds the state of the shell session
	* @exit_status: The integer value of the last executed command's exit code
	* @should_exit: A flag (0 or 1) to determine if the loop should stop
	* @env: A pointer to the array of environment variable strings
	*
	* Description: Manages shell state and environment across functions.
	*/
typedef struct shell_ctx
{
	int exit_status;
	int should_exit;
	char **env;
} shell_ctx_t;

char **copy_env(void);
void execute_command(char **argv, shell_ctx_t *ctx);
char *find_path(char *command, char **env);
int handle_builtin(char **argv, shell_ctx_t *ctx);
void handle_sigint(int sig);
int _setenv(char **argv, shell_ctx_t *ctx);
int _unsetenv(char **argv, shell_ctx_t *ctx);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, size_t n);
char *_strdup(char *str);
char *build_full_path(char *dir, char *command);
char *_strtok(char *str, const char *delim);
int is_delim(char c, const char *delim);

#endif
