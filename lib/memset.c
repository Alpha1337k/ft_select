/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memset.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 23:05:21 by anonymous     #+#    #+#                 */
/*   Updated: 2022/04/14 23:05:58 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
