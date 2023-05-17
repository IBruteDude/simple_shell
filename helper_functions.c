#include "main.h"

/**
 * str_resize - increases the size of a string
 * @str_adr: the address of the input string
 * @size: the size of the input string
 * @n: the number of bytes to add
 * Return: the address of the new string
 */
char *str_resize(char **str_adr, size_t size, size_t n)
{
	size_t i;
	char *temp;

	temp = malloc(size + n);
	if (temp != NULL)
	{
		_memcpy(temp, *str_adr, size);
		free(*str_adr);
		for (i = 0; i < n; i++)
			temp[size + i] = '\0';
	}
	*str_adr = temp;
	return (*str_adr);
}

/**
 * _getline - reads a complete line from input stream into a buffer
 * @lineptr: the address to store the read line
 * @n: the address to store the length of the read line
 * @stream: the specified input stream
 * Return: the length of the read line
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t read_bytes = 0;
	char *line, EOF_byte[1];

	if (stream == stdin)
	{
		line = malloc(1), line[0] = '\0';
		do {
			str_resize(&line, read_bytes, BUF_SIZE);
			read_bytes += read(STDIN_FILENO, line + read_bytes, BUF_SIZE);
			if (line[read_bytes - 1] != '\n')
			{
				read(STDIN_FILENO, EOF_byte, 1);
				if (EOF_byte[0] == '\0')
					break;
				line[read_bytes++] = EOF_byte[0];
			}
		} while (line[read_bytes - 1] != '\n');

		if (read_bytes < *n)
		{
			_memcpy(*lineptr, line, read_bytes);
			(*lineptr)[read_bytes] = '\0';
			free(line);
		}
		else
		{
			line[read_bytes] = '\0';
			free(*lineptr);
			*lineptr = line;
		}
	}
	*n = read_bytes;
	return (read_bytes);
}
