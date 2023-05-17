#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>

#define PROMPT		">>>$ "
#define ARG_MAX		32
#define BUF_SIZE	1024
#define SUCCESS		0
#define READ_ERROR	1
#define CRITICAL	2
#define SLASH       '/'


#define max(a, b) (((a) >= (b)) ? (a) : (b))
#define min(a, b) (((a) <= (b)) ? (a) : (b))
#define isdigit(x) ('0' <= (x) && (x) <= '9')
#define abs(a) (((a) >= 0) ? (a) : -(a))

char *_getenv(char **environ, char *variable);
char *check_exec(char *path, char *cmd);
int sepPath(char **argv, char **file, char **environ, int count);
int search_command(char **argv, char *file, char **environ, int count);
void print_num(int number);
void error(char *file, char *argv, int count ,char *message);
#endif
