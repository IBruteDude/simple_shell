#include "shell.h"

/**
 * print_num - print a number.
 * @number: number to print.
 */
void print_num(int number)
{
	int length = 0, aux = 1, i;
	char c;

	if (number < 0)
		write(STDOUT_FILENO, "-", 1);
	while (number / aux >= 10 || number / aux <= -10)
	{
		length++;
		aux = aux * 10;
	}
	for (i = 0; i <= length; i++)
	{
		if (number < 0)
		{
			c = -((number / aux) % 10) + '0';
			write(STDOUT_FILENO, &c, 1);
		}
		else
		{
			c = ((number / aux) % 10) + '0';
			write(STDOUT_FILENO, &c, 1);
		}
		number = number % aux;
		aux = aux / 10;
	}
}

/**
 * error - handles shell error status and stores it the $? variable
 *
 * @exec_stat: the execution status of the last command
 * @lines_read: the number of lines read by the shell
 * @argv: the shell program argv array
 * @exec_argv: the last command passed arguments array
 */
void error(int exec_stat, int lines_read, const char **argv, char **exec_argv)
{
	char *err;

	switch (exec_stat)
	{
	case FAILURE:
		err = fmt_string("%s: %d: %s: not found\n",
			argv[0], lines_read, exec_argv[0]), _setenv("?", "127", 1);
		break;
	case EOF_FAIL:
		err = fmt_string("%s: %d: Syntax error: Unterminated quoted string\n",
			argv[0], lines_read), _setenv("?", "2", 1);
		break;
	case PERM_DENY:
		err = fmt_string("%s: %d: %s: Permission denied\n",
			argv[0], lines_read, exec_argv[0]), _setenv("?", "127", 1);
		break;
	case BAD_SUB:
		err = fmt_string("%s: %d: Bad substitution\n",
			argv[0], lines_read), _setenv("?", "2", 1);
		break;
	case ILL_NUM:
		err = fmt_string("%s: %d: %s: Illegal number: %s\n",
			argv[0], lines_read, exec_argv[0], exec_argv[1]);
		_setenv("?", "2", 1);
		break;
	case ALIAS_ERROR:
		err = fmt_string("%s: %s not found\n",
			exec_argv[0], exec_argv[1]), _setenv("?", "1", 1);
		break;
	case CMD_LEN:
		err = fmt_string("%s: %d: %s: File name too long\n",
			argv[0], lines_read, exec_argv[0]), _setenv("?", "127", 1);
		break;
	default:
		err = int_to_str(exec_stat);
		_setenv("?", err, 1), free(err);
		err = _strdup("");
	}
	write(STDERR_FILENO, err, _strlen(err)), free(err);
}
