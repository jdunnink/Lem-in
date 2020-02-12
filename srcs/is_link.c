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
	char *first;

	first = ft_strdup_until(one, '-');
	if (ft_strcmp(first, two) == 0)
	{
		free(first);
		return (1);
	}
	free(first);
	return (0);
}

/*
**	is_link checks if the string parament 'link'
**	represents a corrent link between two rooms.
**	returns 1 if valid, 0 if invalid.
*/

int			is_link(char *link, t_data *data)
{
	int		i;
	char	*second;

	i = 0;
	if (link[i] == '-' || link[i] == '#')
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
		error_input(17, data, link);
	return (1);
}
