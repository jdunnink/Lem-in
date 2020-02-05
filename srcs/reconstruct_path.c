/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reconstruct_path.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 14:35:38 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/23 14:35:38 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int		find_depth(int **bfs_data, int rooms)
{
	int i;
	int max_depth;

	i = 0;
	max_depth = 0;
	while (i < rooms)
	{
		if (bfs_data[i][0] > max_depth)
			max_depth = bfs_data[i][0];
		i++;
	}
	return (max_depth + 1);
}

static	void	set_room(t_pathdata *d, int room, int curr_depth, int path)
{
	if (d->bfs_data[room][1] == 0 && d->bfs_data[room][0] == 0)
		d->bfs_data[room][1] = path;
	if (d->bfs_data[room][0] == 0)
		d->bfs_data[room][0] = curr_depth;
}

void			reconstruct_path(t_pathdata *d, int room, int depth, int path)
{
	int i;
	int links;
	int link;
	int orig_depth;

	orig_depth = find_depth(d->bfs_data, d->rooms);
	set_room(d, room, depth, path);
	if (depth == orig_depth)
		return ;
	i = 0;
	links = d->links_num[room];
	while (i < links)
	{
		link = d->links[room][i];
		if (link == -1 || link == d->start || link == d->end)
		{
			i++;
			continue ;
		}
		if (d->bfs_data[link][0] == 0 && d->bfs_data[link][1] == 0)
			reconstruct_path(d, link, depth + 1, path);
		i++;
	}
}
