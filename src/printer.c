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

void	print_data(char **argv)
{
	(void)argv;
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	int x = 0, max_len = get_max_len(argv) + 1;
	int columns = w.ws_col / max_len;
	puts(tgetstr("cl", NULL));
	move(0, 0);
	while (argv[x])
	{
		move((x % columns) * max_len, x / columns);
		printf("%s", argv[x], (x % columns) * max_len, x / columns);
		x++;
	}
	fflush(stdout);
	printf("\ncols: %d %d\n", columns, max_len);
}