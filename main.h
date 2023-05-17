#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#ifdef __linux__
	#include <sys/wait.h>
#endif
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

#define PROMPT		"$ "
#define BUF_SIZE	1024
#define SUCCESS		0
#define FAILURE		1
#define LINE_ERROR	2
#define CRITICAL	3


/* library_functions.c */
size_t _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
void *_memcpy(void *dest, const void *src, size_t n);

/* print_functions.c */
int _putchar(char c);
void _puts(const char *str);
void _puti(int n);
void simple_print(const char *format, int n, const char *str);

/* helper_functions.c */
char *str_resize(char **str_adr, size_t size, size_t n);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/* shell_core.c */
int get_args(char **args_line_adr, int *args_len_adr);
int parse_exec_args(char ***argv_adr, int *argc_adr);
int interactive_mode(int argc, const char *argv[], const char *env[]);

/* argument_processing.c */
int process_args(const char *raw_input, char *cmd_line, int *len_adr);
int check_built_in_commands(int argc, char **argv, const char ** env);
int prefix_PATH(char ***argv_adr, const char **env);
int check_variables(int argc, char **argv, const char **env);
#endif
