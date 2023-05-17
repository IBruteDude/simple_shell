#include "../main.h"


int main(void)
{
	int l = 1, i, argc;
	char *s, **argv;

	parse_exec_args(&argv, &argc);
	for (i = 0; i < argc; i++)
		printf("pointer again: %s\n", argv[i]);
	free(argv[0]), free(argv);
}
