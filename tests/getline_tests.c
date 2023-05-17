#include "../main.h"

int main(int argc, char *argv[])
{
	size_t line_len = 20;
	char *line;

	line = malloc(line_len);
	_getline(&line, &line_len, stdin);

	simple_print("line length: %d\nline: %s\n", line_len, line);
	free(line);
}
