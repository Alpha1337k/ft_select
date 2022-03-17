#include <ft_select.h>
#include <termcap.h>

void help()
{
	write(2, "Usage: ft_select [files..]\n", 28);
}

int main(int argc, char **argv)
{
	t_data *data = get_data();
	if (argc == 1)
	{
		help();
		return 0;
	}

	init(argc, argv);
	fprintf(stderr, "%s%s", get_termcap("ti"), get_termcap("vi"));

	char str[4096 + 1];
	while (1)
	{
		bzero(&str, 4096);
		print_files(data);
		read(STDIN_FILENO, str, 4096);

		if (read_command(data, str) == 0)
			break;
	}

	if (tcsetattr(STDERR_FILENO, 0, &data->original))
		assert(0);
	fprintf(stderr, "%s%s", get_termcap("te"), get_termcap("ve"));

	fflush(stderr);
	print_result(data);
	free(data->selected_map);


	return 0;
}
