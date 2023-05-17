#include "main.h"

/**
 * get_args - receive valid input arguments from the command line
 * @args_line_adr: the address to store the args line
 * @args_len_adr: the address to store the length of the args line
 * Return: the number of lines of input read
 */
int get_args(char **args_line_adr, int *args_len_adr)
{
	int args_len = 1, command_len = BUF_SIZE, lines_read = 0, parse_stat = 0;
	char *command_line = malloc(BUF_SIZE + 1);

	*args_line_adr = malloc(1);
	write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);
	do {
		_getline(&command_line, (size_t *)&command_len, stdin);
		lines_read++;
		str_resize(args_line_adr, args_len, command_len - args_len);
		parse_stat = process_args(command_line, *args_line_adr, &args_len);
		if (parse_stat == LINE_ERROR)
			write(STDOUT_FILENO, "> ", 2);
		else if (parse_stat == CRITICAL)
			exit(EXIT_FAILURE);
	} while (parse_stat != SUCCESS);

	free(command_line);
	*args_len_adr = args_len;
	return (lines_read);
}

/**
 * parse_exec_args - parses the command line arguments into argv
 * @argv_adr: the address to store the parsed arguments
 * @argc_adr: the address to store the number of arguments
 * Return: number of lines read
 */
int parse_exec_args(char ***argv_adr, int *argc_adr)
{
	int argc, args_len, lines_read, i, j;
	char **argv, *args_line;

	lines_read = get_args(&args_line, &args_len);

	for (argc = i = 0; i < args_len; i++) /* count null-terminated args */
		argc += (args_line[i] == '\0');
	argv = malloc((argc + 1) * sizeof(char *));
	argv[0] = args_line;
	for (i = j = 0; i < args_len && j < argc; i++)
		if (args_line[i] == '\0')
			argv[++j] = args_line + i + 1;
	argv[argc] = NULL;

	*argc_adr = argc, *argv_adr = argv;
	return (lines_read);
}

/**
 * interactive_mode - the shell interactive mode REPL
 * @argc: number of input arguments
 * @argv: passed input arguments
 * @env: environment variables
 * Return: the program specific exit status
 */
int interactive_mode(__attribute__((unused)) int argc,
					const char *argv[], const char *env[])
{
	int child_id, child_stat, arg_stat, exec_argc, lines_read = 0;
	char **exec_argv = { NULL };

	while (1)
	{
		exec_argc = arg_stat = 0;
		lines_read += parse_exec_args(&exec_argv, &exec_argc);
		arg_stat = check_built_in_commands(exec_argc, exec_argv, env);
		if (arg_stat == FAILURE)
		{
			arg_stat = check_variables(exec_argc, exec_argv, env);
			if (arg_stat == FAILURE)
				arg_stat = prefix_PATH(&exec_argv, env);
			if (arg_stat == SUCCESS)
			{
				child_id = fork();
				if (child_id == 0)
				{
					arg_stat = 0;
					arg_stat = execve(exec_argv[0],
									(char *const*)exec_argv, (char *const*)env);
					free(exec_argv[0]), free(exec_argv);
					if (arg_stat == -1)
						exit(FAILURE);
					exit(SUCCESS);
				}
				else if (child_id != -1)
					wait(&child_stat), arg_stat = WEXITSTATUS(child_stat);
				else
					perror("Error: forking failed");
			}
		}
		free(exec_argv[0]), free(exec_argv);
		if (arg_stat == FAILURE)
			simple_print("%s: %d: No such file or directory\n",
				lines_read, argv[0]);
	}
	exit(EXIT_SUCCESS);
}



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
