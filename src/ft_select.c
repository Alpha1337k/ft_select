#include <ft_select.h>

void help()
{
	printf("Usage: ft_select [files..]\n");
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		help();
		return 0;
	}
	else
	{
		(void)argv;
	}
	return 0;
}