#include "../shell.h"

char **global_shell_env;
FILE *reading_file;

int main(int ac, const char **av, const char **env)
{
	bool *is_var_place;
	size_t i, len, var_count;
	char *args_line = _strdup("$dd  \\$dsa$USER ${HOME} '$ll\\\\\'$PWD\'$SHLVL'$0$");

	global_shell_env = initialise_shell_env(ac, av, env);
	reading_file = stdin;
	len = _strlen(args_line) + 1;
	/** /
	is_var_place = malloc(len);
	detect_variables(args_line, len, &var_count, is_var_place);

	printf("%s contains %ld vars on:\n", args_line, var_count);
	for (i = 0; i < len; i++)
		putchar('0' + is_var_place[i]);
	/ **/
	printf("old len: %ld\nold line %s\n", len, args_line);
	replace_variables(&args_line, &len);
	printf("%s\n", args_line);
	free(args_line);
}