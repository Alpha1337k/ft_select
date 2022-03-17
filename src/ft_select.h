#ifndef FT_SELECT_H
#define FT_SELECT_H

#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>
#include <unistd.h>
#include <assert.h>
#include <termios.h>
#include <strings.h>
#include <string.h>
#include <sys/ioctl.h>
#include <signal.h>

typedef struct s_data
{
	char **files;
	char *selected_map;
	int file_count;
	int max_file_len;
	int	columns;
	int index;

	struct termios original;
	struct termios term_data;
}	t_data;


void	print_files(t_data *data);
void	print_result(t_data *data);
int		get_max_len(char **argv);

int		read_command(t_data *data, char *str);
void	print_command(char *type);

t_data *get_data();
char *get_termcap(char *str);

void handle_signal(int type);

void init(int argc, char **argv);

#endif
