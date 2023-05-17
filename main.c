#include "main.h"
#include <string.h>

/**
 * process_args - processes special characters
 * @raw_input: the raw stdin read input
 * @cmd_line: the null-separated arguments string
 * @argc_adr: the address to store the number of arguments
 * Return: exit status (0 on success, 1 on wrong input, -1 on critical failure)
 */
int process_args(const char *raw_input, char *cmd_line, int *argc_adr)
{
	static bool escaped, doub_q, sing_q;
	char c;
	int idx = 0, ac = 0;

	if (raw_input == NULL)
		return (CRITICAL);
	while (idx < BUF_SIZE)
		switch (c = raw_input[idx++])
		{
		case ' ':
			*cmd_line++ = (escaped || doub_q || sing_q) ? c : '\0';
			ac += !(escaped || doub_q || sing_q);
			escaped = false;
			break;
		case '\\':
			escaped = !escaped; /* escape switch */
			break;
		case '\"':
			if (escaped || sing_q)
				*cmd_line++ = c, escaped = false;
			else
				doub_q = !doub_q;
			break;
		case '\'':
			if (escaped || doub_q)
				*cmd_line++ = c, escaped = false;
			else
				sing_q = !sing_q;
			break;
		case '\n': case '\0':
			*cmd_line = '\0';
			*argc_adr = ac + 1;
			if (sing_q || doub_q)
				return (READ_ERROR);
			return (SUCCESS);
		default:
			*cmd_line++ = c, escaped = false;
		}
	*cmd_line = '\0';
	return (READ_ERROR);
}

/**
 * parse_exec_args - parses the command line arguments into argv
 * @argv_adr: the address to store the parsed arguments
 * @argc_adr: the address to store the number of arguments
 * Return: number of lines read
 */
int parse_exec_args(char ***argv_adr, int *argc_adr)
{
	int i, j, args_len, read_idx, lines_read = 0, parse_stat;
	char **argv, *temp, *args_line, read_buf[BUF_SIZE];

	args_line = malloc(BUF_SIZE + 1);
	args_line[BUF_SIZE] = '\0';

	read_idx = read(STDIN_FILENO, read_buf, BUF_SIZE);
	lines_read++;

	parse_stat = process_args(read_buf, args_line, argc_adr);
	while (parse_stat != SUCCESS)
	{
		if (parse_stat == CRITICAL)
			exit(EXIT_FAILURE);
		args_len = strlen(args_line);
		temp = malloc(args_len + BUF_SIZE);
		strcpy(temp, args_line);
		free(args_line);
		args_line = temp;

		write(STDOUT_FILENO, "> ", 2);
		read_idx = read(STDIN_FILENO, read_buf, BUF_SIZE);
		lines_read++;
		parse_stat = process_args(read_buf, args_line + args_len, argc_adr);
	}

	argv = malloc((*argc_adr + 1) * sizeof(char *));
	i = j = 0;
	argv[i] = args_line;
	while (j < read_idx)
	{
		if (args_line[j] == '\0')
			argv[++i] = args_line + j + 1;
		j++;
	}

	argv[*argc_adr] = NULL;
	*argv_adr = argv;
	return (lines_read);
}

/**
 * interactive_mode - the shell interactive mode REPL
 * @argc: number of input arguments
 * @argv: passed input arguments
 * @env: environment variables
 * Return: the program specific exit status
 */
int interactive_mode(int argc, const char *argv[], const char *env[])
{
	int child_id, exec_stat, exec_argc, lines_read = 0;
	char **exec_argv = { NULL };

	while (1 || argc == 1)
	{
		exec_argc = exec_stat = 0;
		write(STDOUT_FILENO, PROMPT, sizeof(PROMPT));
		lines_read += parse_exec_args(&exec_argv, &exec_argc);
		if (!strcmp(exec_argv[0], "exit"))
			free(exec_argv[0]), free(exec_argv), exit(0);
		child_id = fork();
		if (child_id == 0)
		{
			exec_stat = execve(exec_argv[0],
							(char *const*)exec_argv, (char *const*)env);
			free(exec_argv[0]), free(exec_argv);
			if (exec_stat == -1)
				printf("%s: %d: No such file or directory\n",
					argv[0], lines_read), exit(-1);
			exit(EXIT_SUCCESS);
		}
		else if (child_id != -1)
			wait(NULL);
		else
			perror("Error: forking failed");
		free(exec_argv[0]), free(exec_argv);
	}

	return (0);
}

/**
 * sighand - handle the ^C signal (optional not a task)
 * @sig: passed signal argument
 */
void sighand(__attribute__((unused)) int sig)
{
	write(STDOUT_FILENO, "YOOOOOOWAIT", sizeof(11));
	interactive_mode(0, NULL, NULL);
}
/**
 * main - Entry point to the shell program
 * @argc: number of input arguments
 * @argv: passed input arguments
 * @env: environment variables
 * Return: the program specific exit status
 *
 * Description: this is the main shell program process
 */
int main(int argc, const char *argv[], const char *env[])
{
	/* used variables and Buffers */

	/* signal(SIGINT, sighand); Warning!! */

	if (argc == 1)
		return (interactive_mode(argc, argv, env));
	/* read input and passed and argument */

	/* process input and execute */

	return (EXIT_SUCCESS);
}
