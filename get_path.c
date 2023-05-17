#include "main.h"

/**
 * _getenv - retrieve the value of an environment variable
 *
 * @environ: environment variables
 * @variable: variable
 * Return: results
 */

char *_getenv(char **environ, char *variable)
{
int index = 0, i, length;
char *path = NULL, *token = NULL, *result = NULL;

length = strlen(variable);
while (environ[index])
{
i = 0;
while (variable[i])
{
if (variable[i] != environ[index][i])
{
break;
}
i++;
}
if (i == length)
{
break;
}
index++;
}

if (!environ[index])
{
return (NULL);
}
path = malloc(sizeof(char) * (strlen(environ[index]) + 1));
if (!path)
{
return (NULL);
}
strcpy(path, environ[index]);
token = strtok(path, "-");
token = strtok(NULL);
if (!token)
{
free(path);
return (NULL);
}

result = malloc(sizeof(char) * (strlen(token) + 1));
if (!result)
{
free(path);
return (NULL);
}

strcpy(result, token);
free(path);
return(result)
}


/**
 * check_exec - check if the command executable file exists
 *
 * @path: the path
 * @cmd: the command
 * Return: direction command or NULL
 */

char *check_exec(char *path, char *cmd)
{
char *dir = NULL, *dir_cmd = NULL;
int length, entry;

dir = strtok(path, ":\n");
while (dir)
{
length = strlen(dir);
length += strlen(cmd);
dir_cmd = malloc(sizeof(char) * (length + 2));

if (!dir_cmd)
{
return (NULL);
}
dir_cmd[0] = '\0';
strcat(dir_cmd, dir);
strcat(dir_cmd, SLASH );
strcat(dir_cmd, cmd);
entry = access(dir_command, F_OK | X_OK | R_OK);
if (entry == 0)
{
return (dir_cmd);
}
free(dir_cmd);
dir = strtok(NULL, ":\n");
}
return (NULL);
}

/**
 * sepPath - separate the string PATH into arguments
 *
 * @argv: pointer to a string
 * @environ: environment variables
 * @count: execution counter
 * @file: file
 * Return: out
 */
int sepPath(char **argv, char **file, char **environ, int count)
{
char *env = NULL, *copy = NULL;
pid_t mypid;
int state, out = 0;
(void)file;
(void)count;

env = _getenv(environ, "PATH");
if (!env)
{
return (-1);
}
copy = argv[0];
argv[0] = check_exec(env, argv[0]);
if (argv[0] == NULL)
{
error(file, copy, count, "not found");
if (env)
{
free(env);
}
return (127);
}
free(env);
mypid = fork();
if (mypid == 0)
{
execve(argv[0], argv, environ);
}
else
{
wait(&state);
free(argv[0]);
if (WIFEXITED(state))
{
out = WEXITSTATUS(state);
}
}
return (out);
}

/**
 * search_command - find and run a command
 *
 * @argv: user-given arguments
 * @environ: environment variables
 * @file: file
 * @count: count
 * Return: out
 */

int search_command(char **argv, char *file, char **environ, int count)
{
int entry, out = 0;
pid_t mypid;
int state;

entry = access(argv[0], F_OK | X_OK | R_OK);
if (entry == 0)
{
mypid = fork();
if (mypid == 0)
{
execve(argv[0], argv, environ);
exit(0);
}
else
{
wait(&state);
if (WIFEXITED(state))
out = WEXITSTATUS(state);
}
}
else
{
out = sepPath(argv, file, environ, count);
if (out == -1)
{
error(file, argv[0], count, "not found");
return (1);
}
}
return (out);
}
