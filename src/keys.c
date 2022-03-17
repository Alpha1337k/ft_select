#include <ft_select.h>

int read_command(t_data *data, char *str)
{
	if (strcmp(str, "\e") == 0)
		return -1;
	else if (strcmp(str, "\n") == 0)
		return 0;
	else if (strcmp(str, "\x7f") == 0 || strcmp(str, "\e[3\x7e") == 0)
	{
		if (data->selected_len == 0)
			return -1;
		if (data->selected_map[data->index])
		{
			data->selected_len--;
			data->selected_map[data->index] = 0;
		}
	}
	else if (strcmp(str, " ") == 0)
	{
		data->selected_map[data->index] = 1;
		data->selected_len++;
		data->index++;
	}
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