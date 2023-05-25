#include "shell.h"

/**
 * replace_variables - replaces shell variables
 * @line_adr: the address of stored input command line
 * @len_adr: the address to store the length of the command line
 * Return: exit status
 */
int replace_variables(char **line_adr, size_t *len_adr)
{
	bool is_var_place[BUF_SIZE];
	char **vals, *line = *line_adr;
	size_t *lens, var_count = 0, stat;
	ssize_t r_idx = 0, w_idx = 0, v_idx = 0, len = *len_adr - 1;

	stat = detect_variables(line, len + 1, &var_count, is_var_place);
	if (stat == BAD_SUB)
		return (stat);
	vals = calloc((var_count + 1), sizeof(char *));
	lens = calloc((var_count + 1), sizeof(size_t));
	vals[var_count] = NULL, lens[var_count] = 0;
	for (v_idx = r_idx = 0; v_idx < (ssize_t) var_count &&
			r_idx < (ssize_t) *len_adr - 1; r_idx++)
		if (is_var_place[r_idx])
			vals[v_idx] = get_var(line + r_idx, lens + v_idx),
			len += (_strlen(vals[v_idx]) - lens[v_idx]), v_idx++;
	line = calloc(len + 2, sizeof(char));
	for (r_idx = w_idx = v_idx = 0; (*line_adr)[r_idx]; r_idx++)
		if (is_var_place[r_idx])
			_strcpy(line + w_idx, vals[v_idx]), w_idx += _strlen(vals[v_idx]),
			r_idx += lens[v_idx] - 1, v_idx++;
		else
			line[w_idx] = (*line_adr)[r_idx], w_idx++;
	line[w_idx] = '\0';
	for (v_idx = 0; v_idx < (ssize_t) var_count; v_idx++)
		free(vals[v_idx]);
	free(*line_adr), free(vals), free(lens);
	*line_adr = line, *len_adr = len + 1;
	return (SUCCESS);
}

/**
 * get_var - get the value of a stored variable
 *
 * @var_name: the address of the start of the variable name
 * @var_len_adr: the address to store the length of the variable name
 * Return: the value of of the variable if found, or an Empty string if not
 */
char *get_var(char *var_name, size_t *var_len_adr)
{
	int i, var_len;
	char *var, *value;

	*var_len_adr = 1;
	var_name++;
	switch (*var_name)
	{
	case '$': case '?': case '*': case '@': case '#':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		var_len = 1;
		break;
	case '{':
		var_name++, *var_len_adr += 2;
		var_len = _strchr(var_name, '}') - var_name;
		break;
	case '\0':
		var_len = 0;
		break;
	default:
		var_len = i = 0;
		while (_strchr(DELIMITERS, var_name[i++]) == NULL)
			var_len++;
	}
	var = malloc(var_len + 1);
	for (i = 0; i < var_len; i++)
		var[i] = var_name[i];
	var[var_len] = '\0';
	value = _strdup(_getenv(var));
	if (value == NULL)
		value = _strdup("");

	*var_len_adr += var_len;
	free(var);
	return (value);
}

/**
 * detect_variables - check for valid variable substitutions
 *
 * @line: the input command line
 * @len: the length of the command line
 * @var_count_adr: the address to store the number of found variables
 * @is_var_place: the array of variable placements
 * Return: exit status
 */
int detect_variables(char *line, size_t len,
						size_t *var_count_adr, bool *is_var_place)
{
	bool escaped = 0, sing_q = 0, doub_q = 0, open_brace = 0;
	int var_count = 0;
	size_t i;

	for (i = 0; i < len; i++)
		is_var_place[i] = false;
	if (_strchr(line, '$') != NULL)
		for (i = 0; i < len; i++)
			switch (line[i])
			{
			case '\\':
				escaped = (sing_q) ? false : !escaped; /* escape switch */
				break;
			case '\'':
				sing_q = (escaped || doub_q) ? sing_q : !sing_q, escaped = false;
				break;
			case '\"':
				doub_q = (escaped || sing_q) ? doub_q : !doub_q, escaped = false;
				break;
			case '{':
				if (!(escaped || sing_q))
					open_brace = true;
				break;
			case '}':
				open_brace = false;
				break;
			case '$':
				if (!escaped)
					var_count += (!sing_q),
					is_var_place[i] = (!sing_q);
				else
					_strcpy(line + i - 1, line + i);
				break;
			default:
				is_var_place[i] = escaped = false;
			}
	*var_count_adr = var_count;
	return ((open_brace) ? BAD_SUB : SUCCESS);
}
