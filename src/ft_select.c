/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_select.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 23:05:13 by anonymous     #+#    #+#                 */
/*   Updated: 2022/04/14 23:05:14 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>
#include <termcap.h>

void	help(void)
{
	write(2, "Usage: ft_select [files..]\n", 28);
}

void	run(t_data *data)
{
	char	str[4096 + 1];
	int		ret;

	while (1)
	{
		ft_memset(str, 0, 4096);
		print_files(data);
		if (read(STDIN_FILENO, str, 4096) <= 0)
			break ;
		ret = read_command(data, str);
		if (ret != 1)
			break ;
	}
	tcsetattr(STDERR_FILENO, 0, &data->original);
	print_termcap("te");
	print_termcap("ve");
	if (ret == 0)
		print_result(data);
	free(data->selected_map);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = get_data();
	if (argc == 1)
	{
		help();
		return (0);
	}
	init(argc, argv);
	print_termcap("ti");
	print_termcap("vi");
	run(data);
	return (0);
}
