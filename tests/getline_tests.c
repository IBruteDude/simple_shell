#include "../shell.h"

/**
 * _getline - reads a complete line from input stream into a buffer
 * @lineptr: the address to store the read line
 * @n: the address to store the length of the read line
 * @stream: the specified input stream
 * Return: the length of the read line
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static size_t read_bytes, crt_read;
	static char *read_buffer, *read_head;
	bool EOF_flag = false;

	read_buffer = malloc(1), read_buffer[0] = '\0';
	do {
		str_resize(&read_buffer, read_bytes, BUF_SIZE);
		crt_read = read(stream->_file, read_buffer + read_bytes, BUF_SIZE);
		read_head = _strchr(read_buffer, '\n');
		if (crt_read == 0)
		{
			EOF_flag = true;
			break;
		}
		read_bytes += crt_read;
	} while (read_head == NULL);

	
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
	*n = read_bytes;
	if (EOF_flag)
		return (EOF);
	return (read_bytes);
}

int main(int argc, char *argv[])
{
	size_t line_len = 20;
	char *line;

	line = malloc(line_len);
	_getline(&line, &line_len, stdin);

	simple_print("line length: %d\nline: %s\n", line_len, line);
	free(line);
}
