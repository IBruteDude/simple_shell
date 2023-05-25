#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>

#ifdef __linux__
	#include <sys/wait.h>
	#define _file \
	_fileno
#endif

#define _max(a, b) (((a) >= (b)) ? (a) : (b))
#define _min(a, b) (((a) <= (b)) ? (a) : (b))
#define _isdigit(x) ('0' <= (x) && (x) <= '9')
#define _isupper(x) ('A' <= (x) && (x) <= 'Z')
#define _islower(x) ('a' <= (x) && (x) <= 'z')
#define _isalpha(x) (_isupper(x) || _islower(x))
#define _isalnum(x) (_isalpha(x) || _isdigit(x))
#define _abs(a) (((a) >= 0) ? (a) : -(a))


#define IFELSE(if_C, if_S, else_S) \
do { \
	if (if_C)	\
	{	\
		if_S;	\
	}	\
	else	\
	{	\
		else_S;	\
	}	\
} while (0)

#define init_malloc(p, s) \
do { \
	typeof(s) _FOO_i = 0; \
	\
	p = malloc(s); \
	while (_FOO_i < s) \
		p[_FOO_i++] = '\0'; \
} while (0)

/* One-line string functions why not?! */
#define _strcat(dest, src) _strcpy((dest) + _strlen(dest), (src))
#define _strdup(s) \
	((s) == NULL ? \
	NULL : \
	_strcpy(calloc((_strlen(s)) + 1, sizeof(char)), (s)))
/* library_functions.c */
size_t _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
void *_memcpy(void *dest, const void *src, size_t n);
char *_strchr(const char *s, int c);

/* print_functions.c */
int _putchar(char c);
int _puts(const char *str);
int _puti(int n);
char *fmt_string(const char *format, ...);
void simple_print(const char *format, int n, const char *str);

/* helper_functions.c */
char *str_resize(char **str_adr, size_t size, size_t n);
int str_to_int(const char *nptr);
char *int_to_str(int n);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char **append_array(char **dest, const char **src, size_t n);

#endif
