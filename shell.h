#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include "getline.h"

#define BUF_SIZE 1024
extern char **environ;

/**
	* struct shell_ctx - Holds the state of the shell session
	* @exit_status: Last executed command's exit code
	* @should_exit: Flag to stop the loop
	* @env: Pointer to heap-allocated environment variables
	*/
typedef struct shell_ctx
{
	int exit_status;
	int should_exit;
	char **env;
} shell_ctx_t;

void execute_command(char **argv, shell_ctx_t *ctx);
char *find_path(char *command, char **env);
int handle_builtin(char **argv, shell_ctx_t *ctx);
void handle_sigint(int sig);
int _cd(char **argv, shell_ctx_t *ctx);
int _setenv(char **argv, shell_ctx_t *ctx);
int _unsetenv(char **argv, shell_ctx_t *ctx);
char **copy_env(void);
char *_getenv(char *name, char **env);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, size_t n);
char *_strdup(char *str);
char *_strtok(char *str, const char *delim);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *build_full_path(char *dir, char *command);
int is_delim(char c, const char *delim);

#endif
