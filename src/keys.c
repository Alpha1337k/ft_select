#include <ft_select.h>

int read_command(t_data *data, char *str)
{
	if (strcmp(str, "\e") == 0 || strcmp(str, "c") == 0)
		return 0;
	else if (strcmp(str, "\b") == 0 || strcmp(str, "\x7f") == 0)
		data->selected_map[data->index] = 0;
	else if (strcmp(str, " ") == 0)
		data->selected_map[data->index] = 1;
	else if (strcmp(str, "\e[A") == 0 || strcmp(str, "w") == 0)
		data->index -= data->columns;
	else if (strcmp(str, "\e[D") == 0 || strcmp(str, "a") == 0)
		data->index--;
	else if (strcmp(str, "\e[B") == 0 || strcmp(str, "s") == 0)
		data->index += data->columns;
	else if (strcmp(str, "\e[C") == 0 || strcmp(str, "d") == 0)
		data->index++;
	if (data->index >= data->file_count)
		data->index = data->index - data->file_count;
	else if (data->index < 0)
		data->index = data->file_count + data->index;
	return 1;
}