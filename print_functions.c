#include "shell.h"

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
 * @s: input string
 * Return: the number of printed bytes
 */
int _puts(const char *s)
{
	if (s == NULL)
		s = "(nil)";
	return (write(1, s, _strlen(s)));
	/* _putchar('\n'); */
}
/**
 * _puti - prints an integer to standard output
 * @n: input integer
 * Return: returns the length of printed integer
 */
int _puti(int n)
{
	int len = 0, mask = 1000000000U /* pow(10, floor(log10(INT_MAX))) */;

	if (n == 0 || n == INT_MIN)
	{
		if (n == INT_MIN)
			len += _puti(n / 10), len += _putchar('0' + -(INT_MIN % 10));
		else
			len += _putchar('0');
		return (len);
	}

	if (n < 0)
		len += _putchar('-'), n = -n;

	while (n / mask == 0)
		mask /= 10;
	while (mask != 0)
		len += _putchar('0' + n / mask), n %= mask, mask /= 10;
	return (len);
}
/**
 * fmt_string - creates a formatted string from input arguments
 *
 * @format: the format string
 * Return: the created formatted string
 */
char *fmt_string(const char *format, ...)
{
	int i = 0, w_idx, arg_idx = 0, args_size = 0, len = 0;
	char c, *str, **args;
	va_list values;

	va_start(values, format);
	while (format[i])
		args_size += (format[i++] == '%');
	args = calloc(args_size + 1, sizeof(char *));
	i = 0;
	while ((c = format[i++]) != '\0')
		if (c == '%')
			switch (format[i++])
			{
			case 'i': case 'd':
				args[arg_idx] = int_to_str(va_arg(values, int)),
				len += _strlen(args[arg_idx]) - 1, arg_idx++;
				break;
			case 's':
				args[arg_idx] = va_arg(values, char *);
				if (args[arg_idx] != NULL)
					args[arg_idx] = _strdup((char *)args[arg_idx]);
				else
					args[arg_idx] = _strdup("(nil)");
				len += _strlen(args[arg_idx]) - 1, arg_idx++;
				break;
			}
	len += _strlen(format);
	str = malloc(len + 1);
	for (arg_idx = w_idx = i = 0; format[i] != '\0' && w_idx < len; i++)
		if (format[i] == '%' && (format[i + 1] == 's' || format[i + 1] == 'd'))
			_strcpy(str + w_idx, args[arg_idx]),
			w_idx += _strlen(args[arg_idx]), arg_idx++, i += 1;
		else
			str[w_idx] = format[i], w_idx++;
	str[w_idx] = '\0';
	for (i = 0; i < args_size; i++)
		free(args[i]);
	free(args);
	va_end(values);
	return (str);
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
