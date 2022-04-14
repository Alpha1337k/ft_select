#include <ft_select.h>

int	read_arrows(t_data *data, char *str)
{
	if (ft_strcmp(str, "\e[A") == 0 || ft_strcmp(str, "w") == 0)
		data->index -= data->columns;
	else if (ft_strcmp(str, "\e[D") == 0 || ft_strcmp(str, "a") == 0)
		data->index--;
	else if (ft_strcmp(str, "\e[B") == 0 || ft_strcmp(str, "s") == 0)
		data->index += data->columns;
	else if (ft_strcmp(str, "\e[C") == 0 || ft_strcmp(str, "d") == 0)
		data->index++;
	if (data->index >= data->file_count)
		data->index = data->index - data->file_count;
	else if (data->index < 0)
		data->index = data->file_count + data->index;
	return (1);
}

int	read_command(t_data *data, char *str)
{
	if (ft_strcmp(str, "\e") == 0)
		return (-1);
	else if (ft_strcmp(str, "\n") == 0)
		return (0);
	else if (ft_strcmp(str, "\x7f") == 0 || ft_strcmp(str, "\e[3\x7e") == 0)
	{
		if (data->selected_len == 0)
			return (-1);
		if (data->selected_map[data->index])
		{
			data->selected_len--;
			data->selected_map[data->index] = 0;
		}
	}
	else if (ft_strcmp(str, " ") == 0)
	{
		data->selected_map[data->index] = 1;
		data->selected_len++;
		data->index++;
	}
	return (read_arrows(data, str));
}
