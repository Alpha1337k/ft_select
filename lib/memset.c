void	*ft_memset(void *d, char c, int n)
{
	char	*data;
	int		x;

	x = 0;
	data = (char *)d;
	while (x < n)
	{
		data[x] = c;
		x++;
	}
	return (data);
}
