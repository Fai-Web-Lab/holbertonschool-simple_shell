#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

#define BUFFER_SIZE 1024
#define PROMPT_TEXT "$ "
#define ERR_FILE "No such file or directory\n"
#define ERR_FOUND "not found\n"

int execute_command(char *line, char *prog_name, int line_number);
void run_shell(char *prog_name);
int run_external_command(char **argv);
int execute_builtin(char **argv);
char *find_command(char *cmd);
char **split_line(char *line);
void free_argv(char **argv);
int _strcmp(char *s1, char *s2);

#endif
