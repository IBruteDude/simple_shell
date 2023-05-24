#include "shell.h"

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
	_memcpy(temp, *str_adr, size);
	free(*str_adr);
	for (i = 0; i < n; i++)
		temp[size + i] = '\0';
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
	size_t read_bytes = 0, read_val;
	char *line;
	bool EOF_flag = false;

	line = malloc(1), line[0] = '\0';
	do {
		str_resize(&line, read_bytes, BUF_SIZE);
		read_val = read(stream->_file, line + read_bytes, BUF_SIZE);
		if (read_val == 0)
		{
			EOF_flag = true;
			break;
		}
		read_bytes += read_val;
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
	*n = read_bytes;
	if (EOF_flag)
		return (EOF);
	return (read_bytes);
}


/**
 * str_to_int - convert string to int
 * @nptr: input string
 * Return: -1 if string is invalid, num if successful
 */
int str_to_int(const char *nptr)
{
	int num = 0;

	while (*nptr)
	{
		if (!_isdigit(*nptr))
			return (-1);
		num *= 10;
		num += *nptr - '0';
		nptr++;
	}
	return (num);
}
/**
 * int_to_str - creates an string from an integer number
 *
 * @n: input integer
 * Return: the created string
 */
char *int_to_str(int n)
{
	int i, len, mask = 1000000000U /* pow(10, floor(log10(INT_MAX))) */;
	char *str;

	str = malloc(21 * sizeof(char));
	str[20] = '\0';
	if (n == 0 || n == INT_MIN)
	{
		if (n == INT_MIN)
			str = int_to_str(n / 10), len = _strlen(str),
			str[len] = '0' + -(INT_MIN % 10), str[len + 1] = '\0';
		else
			str = _strcpy(str, "0");
		return (str);
	}
	i = 0;
	if (n < 0)
		str[i++] = '-', n = -n;
	while (n / mask == 0)
		mask /= 10;
	while (mask != 0)
		str[i++] = '0' + (n / mask),
		n %= mask, mask /= 10;
	str[i] = '\0';
	return (str);
}

/**
 * append_array - appends n strings from a string array to another
 * @dest: destination array
 * @src: source array
 * @n: number of strings to be copied
 * Return: the new modified string array
 */
char **append_array(char **dest, const char **src, size_t n)
{
	size_t len1 = 0, len2 = 0;
	char **temp;

	/* check input before creating new array */
	if (dest == NULL || src == NULL)
		return (NULL);

	while (dest[len1] != NULL)
		len1++;
	while (src[len2] != NULL)
		len2++;
	n = _min(len2, n);

	/* create and fill the new array */
	temp = (char **) malloc((len1 + n + 1) * sizeof(char *));
	for (len1 = 0; dest[len1] != NULL; len1++)
		temp[len1] = dest[len1], free(dest[len1]);
	for (len2 = 0; len2 < n; len2++)
		temp[len1 + len2] = _strdup(src[len2]);
	temp[len1 + n] = NULL;

	/* assign to new array */
	free(dest);
	dest = temp;
	return (dest);
}

