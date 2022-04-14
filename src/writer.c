#include <ft_select.h>

void	print_termcap(char *type)
{
	char	*toprint;

	toprint = get_termcap(type);
	write(2, toprint, strlen(toprint));
}
