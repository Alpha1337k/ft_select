/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 23:05:06 by anonymous     #+#    #+#                 */
/*   Updated: 2022/04/18 19:17:41 by alpha         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

static void	calc_column(int old, t_data *data)
{
	int	remain;	
	int	new_column;

	if (data->file_count <= data->columns)
	{
		data->index = (old % data->columns) - 1;
		if (data->index < 0)
			data->index = data->file_count - 1;
		return ;
	}
	new_column = (old % data->columns) - 1;
	remain = data->file_count % data->columns;
	if (new_column == -1)
		new_column = data->columns - 1;
	if (new_column <= remain - 1)
		data->index = data->file_count - remain + new_column;
	else
		data->index = data->file_count - remain - data->columns + new_column;
}

static int	read_arrows(t_data *data, char *str)
{
	int	old;

	old = data->index;
	if (ft_strcmp(str, KEY_UP) == 0 || ft_strcmp(str, "w") == 0)
		data->index -= data->columns;
	else if (ft_strcmp(str, KEY_LEFT) == 0 || ft_strcmp(str, "a") == 0)
		data->index--;
	else if (ft_strcmp(str, KEY_DOWN) == 0 || ft_strcmp(str, "s") == 0)
		data->index += data->columns;
	else if (ft_strcmp(str, KEY_RIGHT) == 0 || ft_strcmp(str, "d") == 0)
		data->index++;
	if (data->index >= data->file_count)
	{
		if (data->file_count <= data->columns)
			data->index = old + 1;
		else
			data->index = (old % data->columns) + 1;
		if (data->index >= data->columns || \
		(data->file_count <= data->columns && data->index >= data->file_count))
			data->index = 0;
	}
	else if (data->index < 0)
		calc_column(old, data);
	return (1);
}

int	read_command(t_data *data, char *str)
{
	if (ft_strcmp(str, KEY_ESCAPE) == 0)
		return (-1);
	else if (ft_strcmp(str, "\n") == 0)
		return (0);
	else if (ft_strcmp(str, KEY_BACKSPC) == 0 || ft_strcmp(str, KEY_DLT) == 0)
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
		if (data->index >= data->file_count)
			data->index = 0;
	}
	return (read_arrows(data, str));
}
