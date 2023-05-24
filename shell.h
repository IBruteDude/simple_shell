#ifndef SHELL_H
#define SHELL_H

#include "main.h"
#define	PROMPT			"$ "
#define	DELIMITERS		" \t\n\'\"`$(){}&|;<>"
#define	BUF_SIZE		1024
#define	FILE_PATH_MAX	4096
#ifdef	__linux__
#undef	FILENAME_MAX
#define	FILENAME_MAX	256
#endif
#define	FAILURE			-1
#define	SUCCESS			0
#define	CRITICAL		1
#define	LINE_ERROR		2
#define	EOF_FAIL		3
#define	PERM_DENY		4
#define	BAD_SUB			5
#define	ILL_NUM			6
#define	ALIAS_ERROR		7
#define	CMD_LEN			8
#define	SLASH			"/"

#define EMPTY_COMMAND(s) ((s[0] == s[1]) && (s[0] == '\'' || s[1] == '\"'))
#if 0
/*
*#define _SHELL_FREE(i, argv)					\
*	for (i = 0; global_shell_env[i]; i++)		\
*		free(global_shell_env[i]);				\
*	for (i = i + 1; global_shell_env[i]; i++)	\
*		free(global_shell_env[i]);				\
*	free(global_shell_env);						\
*	if (reading_file != stdin)					\
*		close(reading_file->_file);				\
*	free(argv[0]);								\
*	free(argv)
*/
#endif

/**
 * struct shell_command - an associative struct of shell commands and functions
 *
 * @command: the shell command keyword
 * @shell_function: the shell function used to process the command
 */
typedef struct shell_command
{
	const char *command;
	int (*shell_function)(int, char **);
} cmd_t;

extern char **global_shell_env;
extern FILE *reading_file;

/* shell_core.c */
int shell_main_process(const char *argv[], FILE *stream);
int get_args(char **args_line_adr, int *args_len_adr,
				int *input_flag_adr, FILE *stream);
int shell_free(int exit_status, char **argv);
void signal_handle(int sig);

/* get_path.c */
const char *_getenv(char *variable);
char *check_exec(char *cmd);
int search_command(int argc, char **argv);
int sepPath(char **args);

/* error.c */
void print_num(int number);
void error(int exec_stat, int lines_read, const char **argv, char **exec_argv);

/* argument_processing.c */
int process_args(const char *raw_input, char *cmd_line, int *len_adr);
void parse_args(char *args_line, int args_len,
				char ***argv_adr, int *argc_adr);
int replace_aliases(char **line_adr, size_t *len_adr);

/* variable_handling.c */
char *get_var(char *var_name, size_t *var_len_adr);
int replace_variables(char **args_line, size_t *len_adr);
int detect_variables(char *line, size_t len,
						size_t *var_count_adr, bool *is_var_place);

/* environment_utilities.c */
char **initialise_shell_env(int argc, const char *argv[], const char *env[]);
int _setenv(char *name, char *value, int overwrite);
int _unsetenv(char *name);

/* builtin.c */
int check_builtin_commands(int argc, char **argv);
int shell_alias(int argc, char **argv);
int shell_env(int argc, char **argv);
int shell_exit(int argc, char **argv);

#endif
