#include "shell.h"

/**
 * _getenv - retrieve the value of an environment variable
 *
 * @variable: variable
 * Return: results
 */
const char *_getenv(char *variable)
{
	int start_idx = 0, index, i, len;

	if (_strcmp(variable, "ALIAS") == ' ')
	{
		variable = _strchr(variable, ' ') + 1;
		while (global_shell_env[start_idx])
			start_idx++;
		start_idx++;
	} else if (_strcmp(variable, "SHELL") == ' ')
	{
		variable = _strchr(variable, ' ') + 1;
		while (global_shell_env[start_idx])
			start_idx++;
		start_idx++;
		while (global_shell_env[start_idx])
			start_idx++;
		start_idx++;
	}
	len = _strlen(variable);
	for (index = start_idx; global_shell_env[index] != NULL; index++)
	{
		for (i = 0; global_shell_env[index][i] != '\0' && i < len; i++)
			if (global_shell_env[index][i] != variable[i])
				break;
		if (global_shell_env[index][i] == '=')
			break;
	}

	if (global_shell_env[index] == NULL)
		return (NULL);
	return (global_shell_env[index] + len + 1);
}


/**
 * check_exec - check if the command executable file exists
 *
 * @cmd: the command
 * Return: direction command or NULL
 */
char *check_exec(char *cmd)
{
	char *path, *dir, *dir_cmd = NULL, *read_index;
	int entry;

	if (cmd == NULL)
		return (NULL);
	/* dir = strtok(path, ":\n"); */
	path = _strdup(_getenv("PATH"));
	dir = path;
	do {
		read_index = _strchr(dir, ':');
		if (read_index == NULL)
		{
			if (_strlen(dir) != 0)
				read_index = dir + _strlen(dir) - 1,
				*(read_index + 1) = '\0';
		}
		else
		{
			*read_index = '\0';
		}
		dir_cmd = fmt_string("%s/%s", dir, cmd);
		entry = access(dir_cmd, F_OK | X_OK | R_OK);
		if (entry == 0)
			break;
		free(dir_cmd);
		dir_cmd = NULL;
		/* dir = strtok(NULL, ":\n"); */
		dir = read_index + 1;
	} while (read_index != NULL);
	free(path);
	return (dir_cmd);
}

/**
 * sepPath - separate the string PATH into arguments
 *
 * @args: user-given arguments
 * Return: out
 */
int sepPath(char **args)
{
	char *full_path;
	pid_t mypid;
	int state;

	full_path = check_exec(args[0]);
	if (full_path == NULL)
		return (FAILURE);
	mypid = fork();
	if (mypid == 0)
	{
		execve(full_path, args, (char * const*)global_shell_env);
		free(full_path), shell_free(FAILURE, args);
	}
	else if (mypid == -1)
	{
		perror("Error: forking failed\n"),
		shell_free(EXIT_FAILURE, args);
	}
	else
	{
		free(full_path);
		wait(&state);
		if (WIFEXITED(state))
			return (WEXITSTATUS(state));
	}
	return (FAILURE);
}

/**
 * search_command - find and run a command
 *
 * @argc: number of arguments
 * @argv: user-given arguments
 * Return: out
 */

int search_command(int argc, char **argv)
{
	int entry, state;
	pid_t mypid;

	if (argv[0] == NULL)
		return (BAD_SUB);
	if (_strlen(argv[0]) >= FILENAME_MAX)
		return (CMD_LEN);
	if (argv[0][0] == '\0')
		return (SUCCESS);
	state = check_builtin_commands(argc, argv);
	if (state != FAILURE)
		return (state);
	entry = access(argv[0], F_OK | X_OK | R_OK);
	if (entry == 0)
	{
		mypid = fork();
		if (mypid == 0)
		{
			execve(argv[0], argv, (char * const*)global_shell_env);
			free(argv[0]), free(argv), exit(FAILURE);
		}
		else if (mypid == -1)
		{
			free(argv[0]), free(argv);
			perror("Error: forking failed\n"), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&state);
			if (WIFEXITED(state))
				return (WEXITSTATUS(state));
		}
	}
	return (sepPath(argv));
}
