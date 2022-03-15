#include <ft_select.h>
#include <termcap.h>


void help()
{
	write(2, "Usage: ft_select [files..]\n", 28);
}

int main(int argc, char **argv)
{
	struct termios term_data, original;
	t_data data;

	if (argc == 1)
	{
		help();
		return 0;
	}
	(void)argv;
	if (isatty(STDOUT_FILENO) == 0)
	{
		write(2, "Error: terminal expected\n", 26);
		return (1);
	}

	tcgetattr(STDIN_FILENO, &term_data);
	tcgetattr(STDIN_FILENO, &original);

	data.files = &argv[1];
	data.file_count = argc - 1;
	data.max_file_len = get_max_len(data.files) + 1;
	data.index = 0;
	data.selected_map = malloc(sizeof(char) * data.file_count);
	data.columns = 0;

	printf("%d %d %d\n", term_data.c_lflag, term_data.c_lflag & ICANON, term_data.c_lflag ^ 2);

	term_data.c_lflag = term_data.c_lflag ^ (ICANON | ECHO);


	assert(tcsetattr(STDIN_FILENO, 0, &term_data) != -1);


    char buf[1024];

    tgetent(buf, getenv("TERM"));
	char str[4096 + 1];
	while (1)
	{
		print_files(&data);
		read(STDIN_FILENO, str, 4096);

		if (read_command(&data, str) == 0)
			break;
		bzero(&str, 4096);
	}
	
	assert(tcsetattr(STDIN_FILENO, 0, &original) != -1);

	return 0;
}
