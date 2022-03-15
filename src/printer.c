#include <ft_select.h>

int		get_max_len(char **argv)
{
	int max = 0, len, x = 0;
	while (argv[x])
	{
		len = strlen(argv[x]);
		if (len > max)
			max = len;
		x++;
	}
	return max;
}

void	move(int x, int y)
{
	printf("%s", (tgoto(tgetstr("cm", NULL), x, y)));
}

int		calculate_row_offset(t_data *data, struct winsize w)
{
	static int last_render_offset = 0;

	int needed_rows = (data->file_count / data->columns) - 1;

	if (needed_rows < w.ws_row)
		return 0;

	int index_row = data->index / data->columns;

	if (index_row < last_render_offset)
		last_render_offset = index_row;
	else if (index_row > last_render_offset + w.ws_row - 1)
		last_render_offset = index_row - w.ws_row + 1;
	return last_render_offset;
}

void	print_files(t_data *data)
{
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	data->columns = w.ws_col / data->max_file_len;
	if (data->columns == 0)
		data->columns = 1;
	int offset = calculate_row_offset(data, w);
	int x = data->columns * offset;

	printf("%s", tgetstr("cl", NULL));
	move(0, 0);
	while (data->files[x] && x / data->columns < offset + w.ws_row)
	{
		move((x % data->columns) * data->max_file_len, (x / data->columns) - offset);
		if (x == data->index && data->selected_map[x] == 1)
		{
			printf("%s%s%s%s%s", tgetstr("us", NULL), tgetstr("mr", NULL), data->files[x], tgetstr("ue", NULL), tgetstr("me", NULL));
		}
		else if (x == data->index)
		{
			printf("%s%s%s", tgetstr("us", NULL), data->files[x], tgetstr("ue", NULL));
		}
		else if (data->selected_map[x] == 1)
		{
			printf("%s%s%s", tgetstr("mr", NULL), data->files[x], tgetstr("me", NULL));
		}
		else
			printf("%s", data->files[x]);
		x++;
	}
	if (data->files[x] == 0)
		printf("\n");
	else
		fflush(stdout);
}

void	print_result(t_data *data)
{
	int x = 0;
	int is_not_first = 0;

	printf("\n");
	while (data->files[x])
	{
		if (data->selected_map[x])
		{
			if (is_not_first == 1)
			{
				printf(" ");
			}
			else
				is_not_first = 1;
			printf("%s", data->files[x]);
		}
		x++;
	}
	printf("\n");
}