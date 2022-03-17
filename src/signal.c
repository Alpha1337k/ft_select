#include <ft_select.h>

void handle_signal(int type)
{
	(void)type;
	t_data *data = get_data();

	if (type == SIGWINCH)
	{
		print_files(data);
		return;
	}

	free(data->selected_map);
	fprintf(stderr, "%s%s", get_termcap("te"), get_termcap("ve"));
	assert(tcsetattr(STDERR_FILENO, 0, &data->original) != -1);

	exit(1);
}