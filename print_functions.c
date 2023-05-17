#include "main.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
		return (write(1, &c, 1));
}
/**
 * _puts - prints a string to standard output
 * @str: input string
 */
void _puts(const char *str)
{
	if (str)
		write(1, str, _strlen(str));
	/* _putchar('\n'); */
}
/**
 * _puti - prints an integer to standard output
 * @n: input integer
 */
void _puti(int n)
{
	int mask = 1000000000U;

	if (n == 0 || n == INT_MIN)
	{
		if (n == INT_MIN)
			_puti(n / 10), _putchar('0' + INT_MIN % 10);
		else
			_putchar('0');
		return;
	}

	if (n < 0)
		_putchar('-'), n = -n;

	while (n / mask == 0)
		mask /= 10;
	while (mask != 0)
		_putchar('0' + n / mask), n %= mask, mask /= 10;
}
/**
 * simple_print - prints a formatted string with an optional int and string
 * @format: formatting string
 * @n: input integer
 * @str: input string
 */
void simple_print(const char *format, int n, const char *str)
{
	int i;

	for (i = 0; format[i] != '\0'; i++)
		if (format[i] == '%')
			switch (format[++i])
			{
			case 'd': case 'i':
				_puti(n);
				break;
			case 's':
				_puts(str);
				break;
			}
		else
			_putchar(format[i]);
}
