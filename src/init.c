/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 23:05:09 by anonymous     #+#    #+#                 */
/*   Updated: 2022/04/18 19:17:27 by alpha         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

static void	signal_setup(void)
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

void	load_data(t_data *data, int argc, char **argv)
{
	if (argv != 0)
	{
		data->files = &argv[1];
		data->file_count = argc - 1;
		data->max_file_len = get_max_len(data->files) + 1;
		data->index = 0;
		data->selected_map = malloc(data->file_count * sizeof(char));
		if (!data->selected_map)
		{
			write(2, "Error: malloc fail\n", 19);
			exit(1);
		}
		ft_memset(data->selected_map, 0, data->file_count);
	}
	data->columns = 0;
	data->term_data.c_lflag &= ~(ICANON | ECHO);
}

void	init(int argc, char **argv)
{
	t_data	*data;
	char	buf[1024];

	data = get_data();
	if (isatty(STDERR_FILENO) == 0)
	{
		write(2, "Error: terminal expected\n", 25);
		exit(1);
	}
	if (tgetent(buf, getenv("TERM")) < 1)
	{
		write(2, "Error: no enviroment\n", 21);
		exit(1);
	}
	tcgetattr(STDERR_FILENO, &data->original);
	tcgetattr(STDERR_FILENO, &data->term_data);
	load_data(data, argc, argv);
	tcsetattr(STDERR_FILENO, 0, &data->term_data);
	signal_setup();
}
