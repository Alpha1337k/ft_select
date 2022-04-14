/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 23:05:01 by anonymous     #+#    #+#                 */
/*   Updated: 2022/04/14 23:06:57 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	handle_exit(int type, t_data *data)
{
	tcsetattr(STDERR_FILENO, 0, &data->original);
	print_termcap("te");
	print_termcap("ve");
	if (type == SIGTSTP)
	{
		signal(SIGTSTP, SIG_DFL);
		ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
	}
	else
	{
		free(data->selected_map);
		exit(1);
	}
}

void	handle_signal(int type)
{
	t_data	*data;

	data = get_data();
	if (type == SIGCONT)
	{
		init(0, 0);
		print_termcap("ti");
		print_termcap("vi");
		print_files(data);
	}
	else if (type == SIGWINCH)
		print_files(data);
	else
	{
		handle_exit(type, data);
	}
}
