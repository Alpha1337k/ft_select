#include <ft_select.h>
#include <termcap.h>

void help()
{
	write(2, "Usage: ft_select [files..]\n", 28);
}

void run(t_data *data)
{
	char str[4096 + 1];
	int ret;
	while (1)
	{
		bzero(&str, 4096);
		print_files(data);
		read(STDIN_FILENO, str, 4096);

		ret = read_command(data, str); 
		if (ret != 1)
			break;	
	}
	if (tcsetattr(STDERR_FILENO, 0, &data->original))
		assert(0);
	fprintf(stderr, "%s%s", get_termcap("te"), get_termcap("ve"));

	fflush(stderr);
	if (ret == 0)
		print_result(data);
	free(data->selected_map);
	exit(0);
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
	run(data);


	return 0;
}
