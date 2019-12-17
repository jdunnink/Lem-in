/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_link.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 19:21:13 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:45:59 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int	check_dup(char *one, char *two)
{
	if (ft_strcmp(one, two) == 0)
		return (1);
	return (0);
}

int			is_link(char *link)
{
	int		i;
	char	*second;

	i = 0;
	if (link[i] == '-')
		return (0);
	if (ft_cinstr(link, '-') == 0)
		return (0);
	while (link[i] != '\0')
	{
		if (ft_isprint((int)link[i]) == 0)
			return (0);
		if (link[i] == '-')
			second = &(link[i + 1]);
		i++;
	}
	if (link[i - 1] == '-')
		return (0);
	if (check_dup(link, second) == 1)
		return (0);
	return (1);
}
