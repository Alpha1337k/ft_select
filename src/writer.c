/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   writer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 23:04:56 by anonymous     #+#    #+#                 */
/*   Updated: 2022/04/14 23:04:56 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	print_termcap(char *type)
{
	char	*toprint;

	toprint = get_termcap(type);
	write(2, toprint, strlen(toprint));
}
