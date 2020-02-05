/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_upconvergence.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 13:16:36 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/05 13:16:37 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	is_upconvergence(t_pathdata *d, int room)
{
	int i;
	int links;
	int	link;
	int up_streams;

	links = d->links_num[room];
	up_streams = 0;
	i = 0;
	while (i < links)
	{
		link = d->links[room][i];
		if (link == d->end)
			up_streams++;
		if (link != -1 && d->bfs_data[link][1] == d->bfs_data[room][1])
			if (d->bfs_data[link][0] >= d->bfs_data[room][0] &&
				d->bfs_data[link][0] > 0)
				up_streams++;
		i++;
	}
	return (up_streams);
}
