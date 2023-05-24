#include "../shell.h"

int main(int argc, const char *argv[], const char *env[])
{
	char **test_env = malloc (10 * sizeof(char *));
	char *arr[] = {"PHASAD=ZEBALAH", "ALHAK=BATEL", "EMA3A=MOFAKER", NULL, "la='ls -a'", "Bismillah='Bi Esm Allah'", NULL, NULL};
	int i;
	for (i = 0; i < 8; i++)
		test_env[i] = _strdup(arr[i]);
	global_shell_env = test_env;
	/**/
	for (i = 0; i < 8; i++)
		simple_print("test_env[%d] = %s\n", i, (const char *) test_env[i]);
	_setenv("ALHAK", "MONTASER", 1);
	for (i = 0; i < 8; i++)
		simple_print("test_env[%d] = %s\n", i, (const char *) test_env[i]);
	_unsetenv("PHASAD");
	for (i = 0; i < 8; i++)
		simple_print("test_env[%d] = %s\n", i, (const char *) test_env[i]);
	_setenv("ALLAH", "KABEER", 1);
	for (i = 0; i < 8; i++)
		simple_print("test_env[%d] = %s\n", i, (const char *) test_env[i]);
	_setenv("EMA3A", "3ALEM", 0);
	for (i = 0; i < 8; i++)
		simple_print("test_env[%d] = %s\n", i, (const char *) test_env[i]);
	_unsetenv("EMA3A");
	for (i = 0; i < 8; i++)
		simple_print("test_env[%d] = %s\n", i, (const char *) test_env[i]);
	/**/

	for (i = 0; i < 8; i++)
		simple_print("test_env[%d] = %s\n", i, (const char *) test_env[i]);
	_setenv("HAGAYES", "7AMBALAYES", 2);
	for (i = 0; i < 8; i++)
		simple_print("test_env[%d] = %s\n", i, (const char *) test_env[i]);

	for (i = 0; test_env[i]; i++)
		free(test_env[i]);
	for (i = i + 1; test_env[i]; i++)
		free(test_env[i]);
	free(test_env);
	/** /

	for (i = 0; test_env[i]; i++)
		free(test_env[i]);
	free(test_env);
	test_env = initialise_shell_env(argc, argv, env);
	for (i = 0; test_env[i]; i++)
		simple_print("test_env[%d] = %s\n", i, (const char *) test_env[i]);
	for (i = 0; test_env[i]; i++)
		free(test_env[i]);
	for (i = i + 1; test_env[i]; i++)
		free(test_env[i]);
	free(test_env);

	/ **/
}