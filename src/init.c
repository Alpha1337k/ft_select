#include <ft_select.h>

void signal_setup()
{
	signal(SIGWINCH, handle_signal);
	signal(SIGABRT, handle_signal);
	signal(SIGINT, handle_signal);
	signal(SIGSTOP, handle_signal);
	signal(SIGCONT, handle_signal);
	signal(SIGTSTP, handle_signal);
	signal(SIGKILL, handle_signal);
	signal(SIGQUIT, handle_signal);
}

void load_data(t_data *data, int argc, char **argv)
{
	if (argv != 0)
	{
		data->files = &argv[1];
		data->file_count = argc - 1;
		data->max_file_len = get_max_len(data->files) + 1;
		data->index = 0;
		data->selected_map = calloc(data->file_count, sizeof(char));
	}
	data->columns = 0;
	data->term_data.c_lflag &= ~(ICANON | ECHO);
}


void init(int argc, char **argv)
{
	t_data *data = get_data();
    char buf[1024];

	if (isatty(STDERR_FILENO) == 0)
	{
		write(2, "Error: terminal expected\n", 26);
		exit(1);
	}
	if (tgetent(buf, getenv("TERM")) < 1)
		assert(0);

	tcgetattr(STDERR_FILENO, &data->term_data);
	tcgetattr(STDERR_FILENO, &data->original);
	load_data(data, argc, argv);
	signal_setup();
	assert(tcsetattr(STDERR_FILENO, 0, &data->term_data) != -1);
}