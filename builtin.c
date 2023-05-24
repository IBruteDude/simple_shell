#include "shell.h"

/**
 * check_builtin_commands - checks & executes found built-in shell commands
 *
 * @argc: number of passed arguments
 * @argv: the passed arguments array
 * Return: 0 if executed successfully, -1 if an error was encountered
 */
int check_builtin_commands(int argc, char **argv)
{
	int i;

	cmd_t builtins[] = {
		{"exit", shell_exit},
		{"env", shell_env},
		{"setenv", shell_env},
		{"unsetenv", shell_env},
		{"alias", shell_alias},
		{NULL, NULL}
	};

	for (i = 0; builtins[i].command != NULL; i++)
		if (_strcmp(argv[0], builtins[i].command) == SUCCESS)
			break;

	if (builtins[i].command == NULL)
		return (FAILURE);
	return (builtins[i].shell_function(argc, argv));
}
/**
 * shell_env - the shell exit command function
 *
 * @argc: number of passed arguments
 * @argv: the passed arguments array
 * Return: 0 if executed successfully, -1 if an error was encountered
 */
int shell_env(int argc, char **argv)
{
	int i;

	if (_strcmp(argv[0], "env") == SUCCESS)
	{
		if (argc == 1)
			for (i = 0; global_shell_env[i]; i++)
				_puts(global_shell_env[i]), _putchar('\n');
		return (SUCCESS);
	} else if (_strcmp(argv[0], "setenv") == SUCCESS)
	{
		switch (argc)
		{
			case 3:
				return (_setenv(argv[1], argv[2], 1));
			default:
				return (FAILURE);
		}
	} else if (_strcmp(argv[0], "unsetenv") == SUCCESS)
	{
		switch (argc)
		{
			case 2:
				return (_unsetenv(argv[1]));
			default:
				return (FAILURE);
		}
	}
	return (FAILURE);
}
/**
 * shell_exit - the shell exit command function
 *
 * @argc: number of passed arguments
 * @argv: the passed arguments array
 * Return: 0 if executed successfully, -1 if an error was encountered
 */
int shell_exit(int argc, char **argv)
{
	int exit_status = FAILURE;


	if (argc == 1)
		exit_status = EXIT_SUCCESS;
	else if (_strlen(argv[1]) <= 10) /* strlen("2147483647"); */
		exit_status = str_to_int(argv[1]);

	if (exit_status >= 0)
	{
		exit_status = _min(exit_status, 255);
		shell_free(exit_status, argv);
	}
	return (ILL_NUM);
}
/**
 * shell_alias - the shell exit command function
 *
 * @argc: number of passed arguments
 * @argv: the passed arguments array
 * Return: 0 if executed successfully, -1 if an error was encountered
 */
int shell_alias(int argc, char **argv)
{
	int i, idx = 0;
	char *crt_alias, *value, *query;

	while (global_shell_env[idx])
		idx++;
	if (argc == 1)
	{
		for (i = idx + 1; global_shell_env[i]; i++)
			simple_print("%s\n", 0, global_shell_env[i]);
		return (SUCCESS);
	}
	else
	{
		for (i = 1; i < argc; i++)
		{
			if (_strchr(argv[i], '=') == NULL)
			{
				crt_alias = fmt_string("ALIAS %s", argv[i]);
				query = _strdup(_getenv(crt_alias));
				free(crt_alias);
				if (query == NULL)
					return (ALIAS_ERROR);
				crt_alias = fmt_string("%s=%s", argv[i], query);
				_puts(crt_alias), _putchar('\n');
				free(query), free(crt_alias);
			}
			else
			{
				crt_alias = _strdup(argv[i]);
				value = _strchr(crt_alias, '=');
				*value = '\0';
				_setenv(crt_alias, value + 1, 2);
				free(crt_alias);
			}
		}
		return (SUCCESS);
	}
	return (FAILURE);
}
