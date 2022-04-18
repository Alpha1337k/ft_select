/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_select.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 23:05:11 by anonymous     #+#    #+#                 */
/*   Updated: 2022/04/18 19:19:55 by alpha         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdio.h>
# include <stdlib.h>
# include <termcap.h>
# include <unistd.h>
# include <assert.h>
# include <termios.h>
# include <strings.h>
# include <string.h>
# include <sys/ioctl.h>
# include <signal.h>

# define KEY_CTRL_Z	"\x1A"
# define KEY_UP		"\e[A"
# define KEY_DOWN	"\e[B"
# define KEY_RIGHT	"\e[C"
# define KEY_LEFT	"\e[D"
# define KEY_ESCAPE	"\e"
# define KEY_BACKSPC	"\x7f"
# define KEY_DLT	"\e[3\x7e"

typedef struct s_data
{
	char			**files;
	char			*selected_map;
	int				selected_len;
	int				file_count;
	int				max_file_len;
	int				columns;
	int				index;
	struct termios	original;
	struct termios	term_data;
}	t_data;

void	print_files(t_data *data);
void	print_result(t_data *data);
int		get_max_len(char **argv);

int		read_command(t_data *data, char *str);
void	print_command(char *type);
void	print_termcap(char *type);

t_data	*get_data(void);
char	*get_termcap(char *str);

void	handle_signal(int type);

void	init(int argc, char **argv);

/*
	libofzow
*/
void	*ft_memset(void *d, char c, int n);
int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);

#endif
