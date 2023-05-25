#include "shell.h"

/**
 * process_args - processes special characters
 * @cmd_line: the raw stdin read input
 * @args_line: the null-separated arguments string
 * @len_adr: the address to store the number of arguments
 * Return: exit status
 */
int process_args(const char *cmd_line, char *args_line, int *len_adr)
{
	static bool escaped, doub_q, sing_q;
	int c, stat = FAILURE, r_idx = 0, w_idx = *len_adr - 1;

	while (1)
		switch (c = cmd_line[r_idx++])
		{
		case ' ': case '\t':
			args_line[w_idx] = (escaped || doub_q || sing_q) ? c : '\0';
			escaped = false, w_idx += (w_idx > *len_adr - 1);
			while (cmd_line[r_idx] == ' ' || cmd_line[r_idx] == '\t')
				r_idx++;
			break;
		case '\\':
			IFELSE(escaped || sing_q,
				(args_line[w_idx++] = c, escaped = false),
				escaped = (sing_q) ? escaped : !escaped);/* escape switch */
			break;
		case '\"':
			IFELSE(escaped || sing_q,
				(args_line[w_idx++] = c, escaped = false),
				doub_q = !doub_q);
			break;
		case '\'':
			IFELSE(escaped || doub_q,
				(args_line[w_idx++] = c, escaped = false),
				sing_q = !sing_q);
			break;
		case '\n': case '\0': case '#': /* handle comments too */
			IFELSE(sing_q || doub_q || escaped,
				(stat = 2, escaped = false, args_line[w_idx++] = c), stat = 0);
			if (c == '\0'/* EOF */)
				sing_q = doub_q = false;
			args_line[w_idx] = '\0';
			*len_adr = w_idx + 1;
			return (stat);
		default:
			args_line[w_idx++] = c, escaped = false;
		}
	args_line[w_idx] = '\0';
	return (stat);
}

/**
 * parse_args - parses the command line arguments into argv array
 * @line: the input null-separated arguments line
 * @args_len: the length of the arguments line
 * @argv_adr: the address to store the parsed arguments
 * @argc_adr: the address to store the number of arguments
 * Return: number of separated commands
 */
int parse_args(char *line, int args_len, char ***argv_adr, int *argc_adr)
{
	int argc, i, j, command_separators = 1;
	char **argv, cc[3];

	for (argc = i = 0; i < args_len; i++) /* count null-terminated args */
		argc += (line[i] == '\0');
	argv = calloc((argc + 1), sizeof(char *));
	argv[0] = line;
	for (i = j = 0; i < args_len && j < argc; i++)
	{
		if (_strchr(";&|", line[i]) != NULL)
		{
			if (line[i] == '&' || line[i] == '|')
			{
				i++;
				if (line[i - 1] != line[i])
				{
					(*argv_adr)[0] = _strdup("only && and || are valid"),
					(*argv_adr)[1] = NULL, *argc_adr = 1;
					return (STX_ERR);
				}
			}
			i++;
			if (line[i] != '\0')
				if (!ISNAMECHAR(line[i]) || !ISNAMECHAR(line[i + 1]))
				{
					cc[0] = line[i], cc[1] = '\0';
					if (!ISNAMECHAR(line[i + 1]) && line[i] == line[i + 1])
						cc[1] = line[i + 1], cc[2] = '\0';
					(*argv_adr)[0] = fmt_string("\"%s\" unexpected", cc),
					(*argv_adr)[1] = NULL, *argc_adr = 1;
					return (STX_ERR);
				}
			command_separators++;
		}
		if (line[i] == '\0' && line[i + 1] != '\0')
			argv[++j] = line + i + 1;
	}
	argv[argc] = NULL, *argc_adr = argc, *argv_adr = argv;
	return (command_separators);
}

/**
 * replace_aliases - replaces shell variables
 * @line_adr: the address of stored input command line
 * @len_adr: the address to store the length of the command line
 * Return: exit status
 */
int replace_aliases(char **line_adr, size_t *len_adr)
{
	size_t i = 0, res_len, alias_len, len = *len_adr;
	char c, *result, *query, *line = *line_adr;

	if (_isalpha(line[i]) || line[i] == '_')
		while ((c = line[i]) && (_isalnum(c) || c == '_' || c == '-'))
			i++;
	alias_len = i;
	if (i == 0)
		return (FAILURE);
	query = malloc(6 + alias_len + 1), query[6 + alias_len] = '\0';
	_strcpy(query, "ALIAS ");
	for (i = 0; i < alias_len; i++)
		query[i + 6] = line[i];
	result = _strdup(_getenv(query));
	free(query);
	if (result == NULL)
		return (FAILURE);
	_strcpy(result, result + 1);
	res_len = _strlen(result) - 1;
	result[res_len] = '\0';
	if (res_len <= alias_len)
	{
		_strcpy(line, result);
		for (i = alias_len; i <= len; i++)
			line[i - (alias_len - res_len)] = line[i];
		*len_adr -= alias_len - res_len;
	}
	else
	{
		line = malloc(len + (res_len - alias_len) + 1);
		_strcpy(line, result);
		for (i = alias_len; i <= len; i++)
			line[i - (alias_len - res_len)] = (*line_adr)[i];
		free(*line_adr);
		*line_adr = line;
		*len_adr += res_len - alias_len;
	}
	free(result);
	return (SUCCESS);
}
