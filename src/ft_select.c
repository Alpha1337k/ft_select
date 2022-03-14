#include <ft_select.h>
#include <termcap.h>


void help()
{
	write(2, "Usage: ft_select [files..]\n", 28);
}

int main(int argc, char **argv)
{
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
	struct termios data, original;

	tcgetattr(STDIN_FILENO, &data);
	tcgetattr(STDIN_FILENO, &original);


	printf("%d %d %d\n", data.c_lflag, data.c_lflag & ICANON, data.c_lflag ^ 2);

	data.c_lflag = data.c_lflag ^ (ICANON | ECHO);


	assert(tcsetattr(STDIN_FILENO, 0, &data) != -1);


    char buf[1024];

    tgetent(buf, getenv("TERM"));
	// str = tgetstr("cl", NULL);
	char str[4096 + 1];
	while (1)
	{
		print_data(&argv[1]);
		read(STDIN_FILENO, &str, 4096);

		// printf("Data\n$%s", str);
		// fflush(stdout);

		if (strcmp(str, "c") == 0)
			break;
		bzero(&str, 4096);
	}
	
	assert(tcsetattr(STDIN_FILENO, 0, &original) != -1);

	return 0;
}
