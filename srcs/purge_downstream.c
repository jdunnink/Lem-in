/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   purge_downstream.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 13:12:26 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/23 13:12:42 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	clear_room(int *i, int *ret, t_pathdata *d, int room)
{
	*i = 0;
	*ret = 0;
	d->bfs_data[room][0] = 0;
	d->bfs_data[room][1] = 0;
}

static	int		eval_link_1(t_pathdata *d, int link, int next, int path)
{
	if (link != -1 &&
		d->bfs_data[link][0] == next &&
		d->bfs_data[link][1] == path &&
		d->bfs_data[link][0] > 0)
		return (1);
	return (0);
}

static	int		clear_downstream(t_pathdata *d, int room, int orig_depth)
{
	int i;
	int	link;
	int	next;
	int	path;
	int ret;

	if (is_upconvergence(d, room) > 0)
		return (1);
	if (d->bfs_data[room][0] == 1)
	{
		reconstruct_path(d, room, 1, d->bfs_data[room][1]);
		return (0);
	}
	next = d->bfs_data[room][0] - 1;
	path = d->bfs_data[room][1];
	clear_room(&i, &ret, d, room);
	while (i < d->links_num[room])
	{
		link = d->links[room][i];
		if (eval_link_1(d, link, next, path) == 1)
			ret = clear_downstream(d, link, orig_depth);
		i++;
	}
	return (ret);
}

static	int		eval_link_2(t_pathdata *d, int link, int room_dis, int path)
{
	if (link != -1 && d->bfs_data[link][1] == path)
	{
		if (d->bfs_data[link][0] < room_dis &&
			d->bfs_data[link][0] > 0)
			return (1);
		return (0);
	}
	return (0);
}

int				purge_downstream(t_pathdata *d, int room, int *curr_depth)
{
	int i;
	int link;
	int	path;
	int room_dis;
	int	ret;

	if (d->bfs_data[room][0] == 1)
	{
		if (is_upconvergence(d, room) > 0)
			return (1);
		reconstruct_path(d, room, 1, d->bfs_data[room][1]);
		return (0);
	}
	path = d->bfs_data[room][1];
	room_dis = d->bfs_data[room][0];
	clear_room(&i, &ret, d, room);
	while (i < d->links_num[room])
	{
		link = d->links[room][i];
		if (eval_link_2(d, link, room_dis, path) == 1)
			ret = clear_downstream(d, link, (*curr_depth) - 1);
		i++;
	}
	return (ret);
}
