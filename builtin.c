#include "shell.h"
/**
 * builtin - indicates the function to perform
 * @s: is the command to be compared
 * Return: function to perform, or NULL otherwise
 */
int (*builtin(char *s))(char *, char **, char *, char **, int, int)
{
int i = 0;
built ops[] = {
{"exit", exitP},
{"env", env},
{NULL, NULL}
};

while (ops[i].comand)
{
if (strcmp(ops[i].comand, s) == 0)
{
return (ops[i].func);
}
i++;
}
return (NULL);
}
