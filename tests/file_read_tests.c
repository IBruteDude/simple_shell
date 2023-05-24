#include "../shell.h"

int main(void)
{
	int fd, r;
	char buffer[BUF_SIZE];

	fd = open("/mnt/d/Projects/alx/shell_project/simple_shell_backup/tests/shell_script_tests.sh", O_RDONLY);

	while ((r = read(fd, buffer, BUF_SIZE)))
		printf("printf: %d\n", printf("%d : %s", r, buffer)), fflush(stdout);
	printf("reading again: %ld\n", read(fd, buffer, BUF_SIZE));
	close(fd);
}