#include <ft_select.h>
#include <termcap.h>

t_data data;

void handle_signal(int type)
{
	(void)type;

	free(data.selected_map);
	tcsetattr(STDERR_FILENO, 0, &data.original);


	exit(1);
}

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

void help()
{
	write(2, "Usage: ft_select [files..]\n", 28);
}

int main(int argc, char **argv)
{
	struct termios term_data;

	if (argc == 1)
	{
		help();
		return 0;
	}
	(void)argv;
	if (isatty(STDERR_FILENO) == 0)
	{
		write(2, "Error: terminal expected\n", 26);
		return (1);
	}

	signal_setup();
	tcgetattr(STDERR_FILENO, &term_data);
	tcgetattr(STDERR_FILENO, &data.original);

	data.files = &argv[1];
	data.file_count = argc - 1;
	data.max_file_len = get_max_len(data.files) + 1;
	data.index = 0;
	data.selected_map = malloc(sizeof(char) * data.file_count);
	data.columns = 0;

	term_data.c_cc[VMIN] = 1;
	term_data.c_cc[VTIME] = 0;
	term_data.c_lflag = term_data.c_lflag ^ (ICANON | ECHO);


	assert(tcsetattr(STDERR_FILENO, 0, &term_data) != -1);


    char buf[1024];

    tgetent(buf, getenv("TERM"));
	char str[4096 + 1];
	while (1)
	{
		bzero(&str, 4096);
		print_files(&data);
		read(STDIN_FILENO, str, 4096);

		if (read_command(&data, str) == 0)
			break;
	}

	print_result(&data);
	
	assert(tcsetattr(STDERR_FILENO, 0, &data.original) != -1);
	free(data.selected_map);


	return 0;
}
