#include <ft_select.h>

void signal_setup();

void handle_signal(int type)
{
	t_data *data = get_data();

	printf("SIGNALZZ %d\n", type);

	if (type == SIGCONT)
	{
		init(0, 0);
		fprintf(stderr, "%s%s", get_termcap("ti"), get_termcap("vi"));
		run(data);
	}
	else if (type == SIGWINCH)
	{
		print_files(data);
	}
	else
	{
		tcsetattr(STDERR_FILENO, 0, &data->original);
		fprintf(stderr, "%s%s", get_termcap("te"), get_termcap("ve"));
			
		fflush(stderr);
		fflush(stdout);

		if (type != SIGTSTP)
		{
			free(data->selected_map);
			exit(1);
		}
		else
		{
			// kkr retarded
			signal(SIGTSTP, SIG_DFL);
			ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
		}
	}

}