#include "shell.h"

/**
 * get_args - receive valid input arguments from the command line
 *
 * @args_line_adr: the address to store the args line
 * @args_len_adr: the address to store the length of the args line
 * @input_flag_adr: the address to store any input flags
 * @stream: the arguments input stream
 * Return: the number of lines of input read
 */
int get_args(char **args_line_adr, int *args_len_adr,
						int *input_flag_adr, FILE *stream)
{
	bool EOF_flag = false, Bad_substitution = false;
	int args_len = 1, lines_read = 0, parse_stat = SUCCESS;
	size_t command_len = BUF_SIZE;
	char *command_line, *args_line;

	args_line = malloc(1), *args_line = '\0';
	init_malloc(command_line, BUF_SIZE);
	if (isatty(stream->_file))
		write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);
	do {
		EOF_flag = (getline(&command_line, &command_len, stream) == EOF);
		if (EOF_flag && command_len == BUF_SIZE)
		{
			if (isatty(stream->_file))
				_putchar('\n');
			free(command_line), free(args_line),
			shell_free(EXIT_SUCCESS, NULL);
		}
		else
		{
			lines_read++;
		}
		str_resize(&args_line, args_len, BUF_SIZE);
		replace_aliases(&command_line, &command_len);
		parse_stat = replace_variables(&command_line, &command_len);
		if (parse_stat == BAD_SUB)
			Bad_substitution = true;
		else
			parse_stat = process_args(command_line, args_line, &args_len);
		if ((parse_stat == LINE_ERROR || parse_stat == BAD_SUB) && !EOF_flag)
			write(STDOUT_FILENO, "> ", (isatty(stream->_file)) ? 2 : 0);
	} while ((parse_stat == LINE_ERROR || parse_stat == BAD_SUB) && !EOF_flag);
	parse_stat = (EMPTY_COMMAND(command_line)) ? PERM_DENY : parse_stat;
	parse_stat = (parse_stat == LINE_ERROR && EOF_flag == true) ? EOF_FAIL :
		parse_stat; if (command_line[command_len - 1] == '\'' && EOF_flag)
		args_line[args_len++] = '\'', args_line[args_len] = '\0';
	parse_stat = (Bad_substitution) ? BAD_SUB : parse_stat;
	free(command_line), *input_flag_adr = parse_stat;
	*args_line_adr = args_line, *args_len_adr = args_len;
	return (lines_read);
}


/**
 * handle_command_separators - it handles separated input commands
 *
 * @cmd_count: number of input commands
 * @lines_read: number of lines read
 * @argv: the shell's passed arguments
 * @exec_argv: the command arguments array
 * Return: successful parse status
 */
int handle_command_separators(int cmd_count, int lines_read,
								const char **argv, char **exec_argv)
{
	int i, j, k, exec_stat;
	char separator;

	j = k = 0;
	for (i = 0; i < cmd_count; i++)
	{
		while (exec_argv[j] && !_strchr(";&|",
			separator = exec_argv[j][0]))
			j++;
		separator = (exec_argv[j]) ? separator : '\0', exec_argv[j] = NULL,
		exec_stat = search_command(j, exec_argv + k);
		if (exec_stat == SUCCESS)
		{
			_setenv("?", "0", 1);
			if (separator == '|')
				break;
		}
		else
		{
			error(exec_stat, _max(lines_read, 1), argv, exec_argv + k);
			if (separator == '&')
				break;
		}
		k = ++j;
	}
	return (SUCCESS);
}
/**
 * shell_main_process - the shell interactive mode REPL
 *
 * @argv: passed input arguments
 * @stream: the input stream of the shell
 * Return: the program specific exit status
 */
int shell_main_process(const char *argv[], FILE *stream)
{
	int parse_stat, args_len, exec_argc, lines_read = 0, sep_cmds;
	char **exec_argv, *args_line = NULL;

	while (1)
	{
		signal(SIGINT, signal_handle);
		exec_argc = parse_stat = 0;
		lines_read += get_args(&args_line, &args_len, &parse_stat, stream);

		sep_cmds = parse_args(args_line, args_len, &exec_argv, &exec_argc);
		if (parse_stat != BAD_SUB && sep_cmds != STX_ERR)
		{
			if (parse_stat != PERM_DENY && parse_stat != EOF_FAIL)
				parse_stat = handle_command_separators(sep_cmds,
											lines_read, argv, exec_argv);
			else
				exec_argv[0] = (parse_stat == PERM_DENY) ? _strdup("") :
					_strdup("Unterminated quoted string"); /* EOF_FAIL */
		}
		parse_stat = (sep_cmds == STX_ERR) ? STX_ERR : parse_stat;
		if (parse_stat != SUCCESS)
			error(parse_stat, _max(lines_read, 1), argv, exec_argv);
		free(args_line);
		free(exec_argv);
	}
}


/**
 * signal_handle - the shell signal handler
 * @sig: passed signal argument
 */
void signal_handle(int sig)
{
	switch (sig)
	{
	case SIGINT:
		if (isatty(stdin->_file))
		_putchar('\n'), write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);
		break;
	case SIGTERM:
		exit(0);
	#ifdef __linux__
	case SIGKILL:
		_exit(0);
	#endif
	}
}

/**
 * shell_free - frees all shell allocated blocks and exits safely
 *
 * @exit_status: the exit status of the shell
 * @argv: the shells proccesses arguments array
 * Return: doesn't return a value, exits immediately
 */
int shell_free(int exit_status, char **argv)
{
	int i;

	for (i = 0; global_shell_env[i]; i++)
		free(global_shell_env[i]);
	for (i = i + 1; global_shell_env[i]; i++)
		free(global_shell_env[i]);
	free(global_shell_env);
	if (reading_file != stdin)
		fclose(reading_file);
	if (argv != NULL)
		free(argv[0]), free(argv);
	exit(exit_status);
}



/*
*
*signal(SIGINT, signal_handle);
*exec_argc = exec_stat = 0;
*lines_read += get_args(&args_line, &args_len, &exec_stat, env, stdin);
*if (exec_stat == SUCCESS)
*	parse_args(args_line, args_len, &exec_argv, &exec_argc),
*	exec_stat = search_command(exec_argc, exec_argv, env);
*else
*	IFELSE((exec_stat = args_len) == PERM_DENY,
*		(exec_argv = malloc(sizeof(char *)),
*		exec_argv[0] = args_line = _strdup("")), ;)
*if (exec_stat != SUCCESS)
*	error(exec_stat, lines_read, argv, exec_argv);
*free(args_line);
*free(exec_argv);
*int child_id, child_stat;
*if (exec_stat == SUCCESS)
*{
*	child_id = fork();
*	if (child_id == 0)
*	{
*		exec_stat = 0;
*		execve(exec_argv[0],
*						(char *const*)exec_argv, (char *const*)env);
*		free(exec_argv[0]), free(exec_argv);
*		if (exec_stat == -1)
*			exit(FAILURE);
*		exit(SUCCESS);
*	}
*	else if (child_id != -1)
*		wait(&child_stat), exec_stat = WEXITSTATUS(child_stat);
*	else
*		perror("Error: forking failed\n");
*}
*/

/* parse_exec_args deprecated implementation without getline */
/**************************************************************
*int parse_exec_args(char ***argv_adr, int *argc_adr)
*{
*	int argc, args_len, lines_read = 0, parse_stat, i, j;
*	char **argv, *args_line, read_buf[BUF_SIZE];
*
*	args_len = 1, args_line = malloc(args_len), args_line[0] = '\0';
*	write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);
*	do
*	{
*		str_resize(&args_line, args_len, BUF_SIZE);
*		read(STDIN_FILENO, read_buf, BUF_SIZE);
*		lines_read++;
*		parse_stat = process_args(read_buf, args_line, &args_len);
*		if (parse_stat == LINE_ERROR)
*			write(STDOUT_FILENO, "> ", 2);
*		else if (parse_stat == CRITICAL)
*			exit(EXIT_FAILURE);
*	} while (parse_stat != SUCCESS);
*
*	for (argc = i = 0; i < args_len; i++)
*		argc += (args_line[i] == '\0');
*	argv = malloc((argc + 1) * sizeof(char *));
*	argv[0] = args_line;
*	for (i = j = 0; i < args_len && j < argc; i++)
*		if (args_line[i] == '\0')
*			argv[++j] = args_line + i + 1;
*	argv[argc] = NULL;
*
*	*argc_adr = argc, *argv_adr = argv;
*	return (lines_read);
*}
**************************************************************/
