#include "../shell.h"

int main(void)
{
	const char *test_env[] = {"PATHfalse=Bismillah", "PATH=Alhamdulillah", NULL},
		 *env[] = {"PATH=::/adsadkka:Pda:we::/:bin", NULL},
		 *real_env[] = {"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Python311/Scripts/:/mnt/c/Python311/:/mnt/c/Windows/system32:/mnt/c/Windows:/mnt/c/Windows/System32/Wbem:/mnt/c/Windows/System32/WindowsPowerShell/v1.0/:/mnt/c/Windows/System32/OpenSSH/:/mnt/c/Program Files/Git/cmd:/mnt/d/Programs/Neovim/bin:/mnt/c/ProgramData/chocolatey/bin:/mnt/d/Programs/Cmake/bin:/mnt/d/Programs/nodejs/:/mnt/c/Users/kamar/AppData/Local/Microsoft/WindowsApps:/mnt/d/Programs/Microsoft VS Code/bin:/mnt/d/Programs/MinGW/bin:/mnt/c/Program Files/Git/usr/bin:/mnt/d/Programs/ghcup/bin:/mnt/d/Programs/php-8.2.4-Win32-vs16-x64:/mnt/c/Users/kamar/AppData/Roaming/npm:/mnt/d/Programs/vcpkg:/mnt/c/Program Files/Git:/mnt/c/tools/neovim/nvim-win64/bin:/mnt/d/Programs/Anaconda3/Scripts:/snap/bin", NULL};
	char *PATH, *full_command_path;

	_puts("Testing path variable fetching:\n");
	PATH = _strdup(_getenv(test_env, "PATH"));
	_puts(PATH);
	if (PATH)
		free(PATH);
	_putchar('\n');

	_puts("Testing complete path file execution:\n");
	PATH = _strdup(_getenv(env, "PATH"));
	full_command_path = check_exec(PATH, "ls");
	_puts(full_command_path);
	if (full_command_path)
		free(full_command_path);
	if (PATH)
		free(PATH);
	_putchar('\n');

	/**/
	_puts("Testing for the real PATH variable:\n");
	PATH = _strdup(_getenv(real_env, "PATH"));
	full_command_path = check_exec(PATH, "ls");
	_puts(full_command_path);
	if (full_command_path)
		free(full_command_path);
	if (PATH)
		free(PATH);
	_putchar('\n');
	/**/
}