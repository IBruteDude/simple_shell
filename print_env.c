#include "shell.h"
/**
 * exitP - close the shell process.
 * @s: string.
 * @argv: user-given arguments.
 * @environ: environment variables.
 * @count: execution counter.
 * @file: file
 * @out: out
 * Return: out
 */
int exitP(char *s, char **argv, char *file, char **environ, int count, int out)
{
(void)environ;

if (argv[1])
{
errorex(file, argv, count, "Illegal number");
return (127);
}
free(argv);
free(s);
exit(out);
}
/**
* env - print environment variables
* @s: string.
* @argv: user-given arguments
* @environ: environment variables
* @count: execution counter
* @file: file
* @out: out
* Return: 0
*/
int env(char *s, char **argv, char *file, char **environ, int count, int out)
{
int i = 0;
(void)s;

if (argv[1] != NULL)
{
error(file, argv[0], count, "No such file or directory");
return (127);
}
while (environ[i])
{
putchar(environ[i]);
write(STDOUT_FILENO, "\n", 1);
i++;
}
return (out);
}
