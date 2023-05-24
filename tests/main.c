#include "../shell.h"

/**
 * main - Entry point to the shell program
 * @argc: number of input arguments
 * @argv: passed input arguments
 * @env: environment variables
 * Return: the program specific exit status
 *
 * Description: this is the main shell program process
 */

char **global_shell_env;
FILE *reading_file;

int main(int argc, const char *argv[], const char *env[])
{
	int fd, SHLVL;
	char *shell_level, *file_path, *error_msg;
	FILE fd_wrapper;

	global_shell_env = initialise_shell_env(argc, argv, env);
	reading_file = stdin;
	if (argc != 1)
	{
		if (argv[1][0] != '/')
		{
			if (_strcmp(argv[1], "../") == argv[1][3])
				file_path = fmt_string("%s/%s", _getenv("ParentPWD"), argv[1]);
			else
				file_path = fmt_string("%s/%s", _getenv("PWD"), argv[1]);
		}
		else
		{
			file_path = _strdup(argv[1]);
		}
		fd = open(file_path, O_RDONLY);
		if (fd == -1)
		{
			error_msg = fmt_string("%s: %d: cannot open %s: No such file\n",
					argv[0], 0, argv[1]);
			write(STDERR_FILENO, error_msg, _strlen(error_msg));
			free(error_msg), free(file_path), shell_free(2, NULL);
		}
		fd_wrapper._file = fd;
		if ((fd_wrapper._file))
		reading_file = &fd_wrapper;
		if (_getenv("SHLVL") != NULL)
		{
			SHLVL = str_to_int(_getenv("SHLVL"));
			shell_level = int_to_str(SHLVL + 1);
			_setenv("SHLVL", shell_level, 1);
			free(shell_level);
		}
	}
	return (shell_main_process(argv, reading_file));
}
