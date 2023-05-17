#include "main.h"

/**
 * printnumber - print a number.
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

void error(char *file, char *argv, int count ,char *message)
{
    putchar(file);
    write(STDOUT_FILENO, ": ", 2);
    print_num(count);
    write(STDOUT_FILENO, ": ", 2);
    putchar(argv);
    write(STDOUT_FILENO, ": ", 2);
    putchar(message);
    write(STDOUT_FILENO, "\n", 1);
}