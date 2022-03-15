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
	fflush(stdout);

}

void	print_files(t_data *data)
{
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	int x = 0;
	data->columns = w.ws_col / data->max_file_len;

	puts(tgetstr("cl", NULL));
	move(0, 0);
	while (data->files[x])
	{
		move((x % data->columns) * data->max_file_len, x / data->columns);
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
	fflush(stdout);
}