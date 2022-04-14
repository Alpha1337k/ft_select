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
		len = strlen(argv[x]);
		if (len > max)
			max = len;
		x++;
	}
	return (max);
}

void	move(int x, int y)
{
	fprintf(stderr, "%s", (tgoto(get_termcap("cm"), x, y)));
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
	fprintf(stderr, "%s", get_termcap("cl"));
	while (d->files[x] && x / d->columns < off + w.ws_row)
	{
		move((x % d->columns) * d->max_file_len, (x / d->columns) - off);
		if (x == d->index && d->selected_map[x] == 1)
			fprintf(stderr, "%s%s%s%s%s", get_termcap("us"), get_termcap("mr"), \
				d->files[x], get_termcap("ue"), get_termcap("me"));
		else if (x == d->index)
			fprintf(stderr, "%s%s%s", get_termcap("us"), d->files[x], \
				get_termcap("ue"));
		else if (d->selected_map[x] == 1)
			fprintf(stderr, "%s%s%s", get_termcap("mr"), d->files[x], \
				get_termcap("me"));
		else
			fprintf(stderr, "%s", d->files[x]);
		x++;
	}
	fflush(stderr);
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
				fprintf(stdout, " ");
			}
			else
				is_not_first = 1;
			fprintf(stdout, "%s", data->files[x]);
		}
		x++;
	}
	if (is_not_first)
		fprintf(stdout, "\n");
}
