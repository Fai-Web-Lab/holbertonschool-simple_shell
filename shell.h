#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 102
#define PROMPT "$ "

extern char **environ;

void run_shell(char *prog_name);
int execute_command(char *line, char *prog_name);
int is_only_spaces(char *str);

#endif
