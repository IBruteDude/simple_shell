#include "../main.h"

/**
 * main - Entry point to the shell program
 * @argc: number of input arguments
 * @argv: passed input arguments
 * @env: environment variables
 * Return: the program specific exit status
 *
 * Description: this is the main shell program process
 */
int main(int argc, const char *argv[], const char *env[])
{
	/* used variables and Buffers */

	/* signal(SIGINT, sighand); Warning!! */

	if (argc == 1)
		return (interactive_mode(argc, argv, env));
	/* read input and passed and argument */

	/* process input and execute */

	return (EXIT_SUCCESS);
}
