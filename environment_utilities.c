#include "shell.h"

/**
 * _setenv - set a value of an environment variable
 *
 * @name: the name of the variable
 * @value: the value of the variable
 * @overwrite: the overwritting selected option
 * Return: exit status
 */
int _setenv(char *name, char *value, int overwrite)
{
	char *var, **env = global_shell_env;
	size_t i, env_size, alias_size, name_len = _strlen(name);

	for (env_size = 0; env[env_size] != NULL; env_size++)
	{
		for (i = 0; env[env_size][i] != '\0' && i < name_len; i++)
			if (env[env_size][i] != name[i])
				break;
		if (env[env_size][i] == '=')
			break;
	}
	if (env[env_size] == NULL)
	{
		alias_size = env_size + 1;
		while (env[alias_size])
			alias_size++;
		env = malloc((alias_size + 5) * sizeof(char *));
		for (i = 0; i < env_size; i++)
			env[i] = global_shell_env[i];
		if (overwrite != 2)
			env[i++] = fmt_string("%s=%s", name, value);
		env[i] = NULL;
		for (i = i + 1; global_shell_env[(overwrite != 2) ? i - 1 : i]; i++)
			env[i] = global_shell_env[(overwrite != 2) ? i - 1 : i];
		if (overwrite == 2)
			env[i++] = fmt_string("%s='%s'", name, value);
		env[i + 1] = env[i] = NULL;
		free(global_shell_env);
		global_shell_env = env;
	}
	else if (overwrite)
	{
		if (_strlen(env[env_size] + name_len + 1) < _strlen(value))
			var = fmt_string("%s=%s", name, value),
			free(global_shell_env[env_size]), global_shell_env[env_size] = var;
		else
			_strcpy(global_shell_env[env_size] + name_len + 1, value);
	}
	return (SUCCESS);
}
/**
 * _unsetenv - unset/remove an environment variable
 *
 * @name: the name of the variable
 * Return: exit status
 */
int _unsetenv(char *name)
{
	const char *adr = _getenv(name);
	char **env = global_shell_env;
	int delete_idx = 0, replace_idx, len = _strlen(name) + 1;

	if (adr != NULL && env[0] != NULL)
	{
		while (env[delete_idx] != adr - len)
			delete_idx++;
		free(env[delete_idx]);
		replace_idx = delete_idx + 1;
		while (env[replace_idx])
			replace_idx++;
		env[delete_idx] = env[replace_idx - 1];
		env[replace_idx - 1] = NULL;
		if (env[replace_idx + 1])
		{
			delete_idx = replace_idx++;
			while (env[replace_idx])
				replace_idx++;
			env[delete_idx] = env[replace_idx - 1];
			env[replace_idx - 1] = NULL;
		}
	}
	return (SUCCESS);
}
/**
 * initialise_shell_env - initialises the shell's environment var array
 *
 * @argc: number of passed arguments to the shell program
 * @argv: the shell's arguments array
 * @env: the shell's passed environment variables array
 * Return: the created env array
 */
char **initialise_shell_env(int argc, const char *argv[],
								const char *env[])
{
	int i = 0, j, shell_args_len = 0, env_size = 0, pid = getpid();
	char **shell_env, *shell_args_line, *parent_pwd;

	while (env[env_size])
		env_size++;
	shell_env = malloc((env_size + 20) * sizeof(char *));

	for (i = 1; i < argc; i++)
		shell_args_len += _strlen(argv[i]) + 2;
	shell_args_line = malloc(_max(shell_args_len, 1)), *shell_args_line = '\0';
	for (i = 1; i < argc; i++)
		_strcat(shell_args_line, argv[i]),
		_strcat(shell_args_line, " ");
	parent_pwd = malloc(FILE_PATH_MAX);
	getcwd(parent_pwd, FILE_PATH_MAX);
	for (j = _strlen(parent_pwd) - 1; j > 0; j--)
		if (parent_pwd[j] == '/')
			break;
	if (j != 0)
		parent_pwd[j] = '\0';

	for (i = 0; i < 10; i++)
		if (i < argc)
			shell_env[i] = fmt_string("%d=%s", i, argv[i]);
		else
			shell_env[i] = fmt_string("%d=", i);
	shell_env[i++] = fmt_string("#=%d", argc);
	shell_env[i++] = fmt_string("*=%s", shell_args_line);
	shell_env[i++] = fmt_string("@=%s", shell_args_line);
	shell_env[i++] = fmt_string("$=%d", pid);
	shell_env[i++] = _strdup("?=");
	shell_env[i++] = _strdup("IFS= \t\n");
	shell_env[i++] = fmt_string("ParentPWD=%s", parent_pwd);
	for (j = 0; env[j] != NULL; j++)
		shell_env[i++] = _strdup(env[j]);
	shell_env[i + 2] = shell_env[i + 1] = shell_env[i] = NULL;
	global_shell_env = shell_env;
	free(parent_pwd);
	free(shell_args_line);
	return (shell_env);
}
