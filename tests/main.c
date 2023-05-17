#include "../main.h"

/**
 * sighand - handle the ^C signal (optional not a task)
 * @sig: passed signal argument
 */
void sighand(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "YOOOOOOWAIT\n", 12);
		interactive_mode(0, NULL, NULL);
	}
}
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
