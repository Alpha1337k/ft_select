#include <ft_select.h>

char	*get_termcap(char *str)
{
	static char	*storage[26][26];
	int			i1;
	int			i2;

	i1 = str[0] - 97;
	i2 = str[1] - 97;
	if (storage[i1][i2] == 0)
		storage[i1][i2] = tgetstr(str, 0);
	if (storage[i1][i2] == 0)
		assert(0);
	return (storage[i1][i2]);
}

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}
