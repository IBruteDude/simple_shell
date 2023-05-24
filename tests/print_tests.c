#include "../shell.h"
#include <stdio.h>

int main(void)
{
	int i, ints[] = {0, INT_MIN, INT_MAX, 12345678, -12345678};
	char *ss;
	/** /
	_puts("printf:\n");
	for (i = 0; i < 5; i++)
		printf("%d\t", ints[i]);
	fflush(stdout);
	_puts("\nprint_num:\n");
	for (i = 0; i < 5; i++)
		print_num(ints[i]), _putchar('\t');
	_puts("\n_puti:\n");
	for (i = 0; i < 5; i++)
		_puti(ints[i]), _putchar('\t');
	_putchar('\n');
	/** /
	_puti(str_to_int("9999999999999999"));
	for (i = 0; i < 5; i++)
	{
		ss = int_to_str(ints[i]);
		_puts(ss) ,_putchar('\n');
		free(ss);
	}
	/**/
	_puts(fmt_string("1%s2%s3||%d||%s\n", "HI", "BYE", 777, "ALHAMDULILLAH"));
}