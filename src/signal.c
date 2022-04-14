#include <ft_select.h>

void	handle_exit(int type, t_data *data)
{
	tcsetattr(STDERR_FILENO, 0, &data->original);
	fprintf(stderr, "%s%s", get_termcap("te"), get_termcap("ve"));
	fflush(stderr);
	if (type == SIGTSTP)
	{
		signal(SIGTSTP, SIG_DFL);
		ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
	}
	else
	{
		free(data->selected_map);
		exit(1);
	}
}

void	handle_signal(int type)
{
	t_data	*data;

	data = get_data();
	if (type == SIGCONT)
	{
		init(0, 0);
		fprintf(stderr, "%s%s", get_termcap("ti"), get_termcap("vi"));
		print_files(data);
	}
	else if (type == SIGWINCH)
		print_files(data);
	else
	{
		handle_exit(type, data);
	}
}
