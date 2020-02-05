/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filter_deadends.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 17:09:38 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/05 09:15:13 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int	count_links(int room, t_data *data)
{
	int i;
	int links;
	int link;
	int count;

	count = 0;
	i = 0;
	links = data->links_num[room];
	while (i < links)
	{
		link = data->links[room][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		else
			count++;
		i++;
	}
	return (count);
}

void		filter_deadends(t_data **data)
{
	t_data	*curr;
	int		i;

	curr = *data;
	i = 0;
	while (i < curr->rooms)
	{
		if (count_links(i, curr) == 1 && i != curr->end && i != curr->start)
		{
			block_link(*data, i);
			i = 0;
		}
		i++;
	}
}
