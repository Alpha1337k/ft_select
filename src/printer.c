/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 23:05:04 by anonymous     #+#    #+#                 */
/*   Updated: 2022/04/14 23:05:04 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

int	get_max_len(char **argv)
{
	int	max;
	int	len;
	int	x;

	max = 0;
	x = 0;
	while (argv[x])
	{
		len = ft_strlen(argv[x]);
		if (len > max)
			max = len;
		x++;
	}
	return (max);
}

void	move(int x, int y)
{
	char	*toprint;

	toprint = tgoto(get_termcap("cm"), x, y);
	write(2, toprint, ft_strlen(toprint));
}

int	calculate_row_offset(t_data *data, struct winsize *w)
{
	static int		last_render_offset = 0;
	int				needed_rows;
	int				index_row;

	ioctl(STDERR_FILENO, TIOCGWINSZ, w);
	data->columns = w->ws_col / data->max_file_len;
	if (data->columns == 0)
		data->columns = 1;
	needed_rows = (data->file_count / data->columns) - 1;
	if (needed_rows < w->ws_row)
		return (0);
	index_row = data->index / data->columns;
	if (index_row < last_render_offset)
		last_render_offset = index_row;
	else if (index_row > last_render_offset + w->ws_row - 1)
		last_render_offset = index_row - w->ws_row + 1;
	return (last_render_offset);
}

void	print_files(t_data *d)
{
	int				off;
	int				x;
	struct winsize	w;

	off = calculate_row_offset(d, &w);
	x = d->columns * off;
	print_termcap("cl");
	while (d->files[x] && x / d->columns < off + w.ws_row)
	{
		move((x % d->columns) * d->max_file_len, (x / d->columns) - off);
		if (x == d->index)
			print_termcap("us");
		if (d->selected_map[x])
			print_termcap("mr");
		write(2, d->files[x], ft_strlen(d->files[x]));
		print_termcap("ue");
		print_termcap("me");
		x++;
	}
}

void	print_result(t_data *data)
{
	int	x;
	int	is_not_first;

	is_not_first = 0;
	x = 0;
	while (data->files[x])
	{
		if (data->selected_map[x])
		{
			if (is_not_first == 1)
			{
				write(1, " ", 1);
			}
			else
				is_not_first = 1;
			write(1, data->files[x], ft_strlen(data->files[x]));
		}
		x++;
	}
	if (is_not_first)
		write(1, "\n", 1);
}
