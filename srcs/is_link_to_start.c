/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_link_to_start.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 16:34:07 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/04 16:34:08 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	is_link_to_start takes the index of the room and checks if
**	this room is connected to the start node. returns 1 if connected
**	0 if not.
**
**	examples:
**
**	room 68 is connected to the start node, which is 45,
**	where room 68 is the first link to 45, and 45 is the second
**	link to 68.
**
**	---------------> data->links[45] = { 68, etc.. }
**	---------------> data->links[45][0] = 68
**
**	---------------> data->links[68] = { 1, 45, etc.. }
**	---------------> data->links[68][1] = 45
*/

int	is_link_to_start(t_pathdata *data, int room)
{
	int i;
	int links;
	int link;
	int	start_conns;

	start_conns = 0;
	i = 0;
	links = data->links_num[data->start];
	while (i < links)
	{
		link = data->links[data->start][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (link == room)
			return (1);
		i++;
	}
	return (0);
}
