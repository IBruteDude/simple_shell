#include "shell.h"

/**
 * _strlen - find the length of a string
 * @str: input string
 * Return: length of the string
 */
size_t _strlen(const char *str)
{
	size_t i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}
/**
 * _strcpy - copys a string
 * @dest: destination address
 * @src: soure address
 * Return: copied destination address
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i = 0;

	while (src[i] != '\0')
		dest[i] = src[i], i++;
	dest[i] = '\0';
	return (dest);
}
/**
 * _strcmp - compute a difference between two strings
 * @s1: first input string
 * @s2: second input string
 * Return: 0 if similar, non-zero otherwise
 */
int _strcmp(const char *s1, const char *s2)
{
	int diff;

	while (!(diff = *s1 - *s2) && (*s1 && *s2))
		s1++, s2++;
	return (diff);
}
/**
 * _memcpy - copies n bytes from the source address to destination address
 * @dest: destinationa address
 * @src: source address
 * @n: number of bytes
 * Return: destination address
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	char *dest_ptr = dest;
	const char *src_ptr = src;

	for (i = 0; i < n; i++)
		dest_ptr[i] = src_ptr[i];
	return (dest);
}
/**
 * _strchr - find the address of a char inside a string
 * @s: input string
 * @c: specified char
 * Return: address of the found char, or NULL if not found
 */
char *_strchr(const char *s, int c)
{
	size_t i = 0;

	while (s[i] != '\0')
		if (s[i++] == c)
			return ((char *)(s + i - 1));
	return (NULL);
}
