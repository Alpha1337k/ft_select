#include <ft_select.h>

void handle_signal(int type)
{
	(void)type;
	t_data *data = get_data();

	fprintf(stderr, "SIGNAL DETECTED %d\n", type);

	free(data->selected_map);
	tcsetattr(STDERR_FILENO, 0, &data->original);

	exit(1);
}