/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   purge_upstream.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 13:11:51 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/23 13:12:16 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int		is_convergence(t_pathdata *d, int room)
{
	int i;
	int links;
	int	l;
	int down_streams;

	links = d->links_num[room];
	down_streams = 0;
	i = 0;
	while (i < links)
	{
		l = d->links[room][i];
		if (l == -1)
		{
			i++;
			continue ;
		}
		if (d->bfs_data[l][1] == d->bfs_data[room][1])
		{
			if (d->bfs_data[l][0] <= d->bfs_data[room][0] &&
				d->bfs_data[l][0] > 0)
				down_streams++;
		}
		i++;
	}
	return (down_streams);
}

static	void	clear_upstream(t_pathdata *d, int room)
{
	int i;
	int links;
	int	link;
	int	next;
	int	path;

	if (is_convergence(d, room) > 1)
		return ;
	i = 0;
	links = d->links_num[room];
	next = d->bfs_data[room][0] + 1;
	path = d->bfs_data[room][1];
	d->bfs_data[room][0] = 0;
	d->bfs_data[room][1] = 0;
	while (i < links)
	{
		link = d->links[room][i];
		if (link != -1 && d->bfs_data[link][0] == next &&
			d->bfs_data[link][1] == path &&
			d->bfs_data[link][0] > 0)
			clear_upstream(d, link);
		i++;
	}
}

void			purge_upstream(t_pathdata *d, int room)
{
	int i;
	int links;
	int l;

	i = 0;
	links = d->links_num[room];
	while (i < links)
	{
		l = d->links[room][i];
		if (l == -1)
		{
			i++;
			continue ;
		}
		if (d->bfs_data[l][1] == d->bfs_data[room][1])
		{
			if (d->bfs_data[l][0] > d->bfs_data[room][0] &&
				d->bfs_data[l][0] > 0)
				clear_upstream(d, l);
		}
		i++;
	}
}
