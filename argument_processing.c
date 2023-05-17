#include "main.h"

/**
 * process_args - processes special characters
 * @raw_input: the raw stdin read input
 * @cmd_line: the null-separated arguments string
 * @len_adr: the address to store the number of arguments
 * Return: exit status (0 on success, 1 on wrong input, -1 on critical failure)
 */
int process_args(const char *raw_input, char *cmd_line, int *len_adr)
{
	static bool escaped, doub_q, sing_q;
	char c;
	int size, read_idx = 0, write_idx = *len_adr - 1;

	size = _strlen(raw_input);
	while (read_idx < size)
		switch (c = raw_input[read_idx++])
		{
		case ' ':
			cmd_line[write_idx++] = (escaped || doub_q || sing_q) ? c : '\0';
			escaped = false;
			while (raw_input[read_idx] == ' ')
				read_idx++;
			break;
		case '\\':
			escaped = !escaped; /* escape switch */
			break;
		case '\"':
			if (escaped || sing_q)
				cmd_line[write_idx++] = c, escaped = false;
			else
				doub_q = !doub_q;
			break;
		case '\'':
			if (escaped || doub_q)
				cmd_line[write_idx++] = c, escaped = false;
			else
				sing_q = !sing_q;
			break;
		case '\n': case '\0': case '#': /* handle comments too */
			cmd_line[write_idx] = '\0';
			*len_adr = write_idx + 1;
			if (escaped || sing_q || doub_q) /* handle unterminated input */
				return (LINE_ERROR);
			return (SUCCESS);
		default:
			cmd_line[write_idx++] = c, escaped = false;
		}
	cmd_line[write_idx] = '\0';
	return (LINE_ERROR);
}

/**
 * check_built_in_commands - checks & executes found built-in shell commands
 * @argc: number of passed arguments
 * @argv: the passed arguments array
 * @env: the environment variables array
 * Return: 0 if executed successfully, -1 if an error was encountered
 */
int check_built_in_commands(int argc, char **argv, const char **env)
{
	if (_strcmp(argv[0], "exit") == SUCCESS)
	{
		free(argv[0]), free(argv);
		if (argc == 1)
			exit(EXIT_SUCCESS);
		/* handle exit arguments */
	}
	else if (_strcmp(argv[0], "env") == SUCCESS)
	{
		int i;

		for (i = 0; env[i] != NULL; i++)
			_puts(env[i]), _putchar('\n');
		return (0);
	}
	else
	{
		/* check for other commands and check for errors before executing */
	}
	return (1);
}
/**
 * prefix_PATH - replaces incomplete argument paths
 * @argv_adr: the address of the arguments array
 * @env: the environment variables array
 * Return: 0 if executed successfully, -1 if an error was encountered
 */
int prefix_PATH(__attribute__((unused)) char ***argv_adr,
				__attribute__((unused)) const char **env)
{
	/* To be implemented */
	return (0);
}
/**
 * check_variables - replaces incomplete argument paths
 * @argc: the number of passed arguments
 * @argv: the passed arguments array
 * @env: the environment variables array
 * Return: 0 if executed successfully, -1 if an error was encountered
 */
int check_variables(__attribute__((unused)) int argc,
					__attribute__((unused)) char **argv,
					__attribute__((unused)) const char **env)
{
	/* To be implemented */
	return (0);
}
