#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

extern char **environ;

void execute_command(char **args);
char *find_path(char *command);
char **tokenize(char *line);
void free_args(char **args);

#endif
