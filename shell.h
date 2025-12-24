#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define PROMPT_TEXT "$ "
#define ERR_FOUND "not found\n"

void run_shell(char *prog_name);
int execute_command(char *line);
char *find_command(char *cmd);
char **split_line(char *line);
void free_argv(char **argv);
int _strcmp(char *s1, char *s2);

#endif
