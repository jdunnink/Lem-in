/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_links.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 15:28:43 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:46:59 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		open_links(t_pathdata *data, int room_index)
{
	int open_links;
	int links_num;
	int link;
	int i;

	i = 0;
	open_links = 0;
	links_num = data->links_num[room_index];
	while (i < links_num)
	{
		link = data->links[room_index][i];
		if (data->state[link] == 0 && data->pheromone[link] < 10000)
			open_links++;
		else if (data->state[link] != 0 && link == data->end)
			open_links++;
		i++;
	}
	return (open_links);
}
