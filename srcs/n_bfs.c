/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_bfs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:32:11 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/05 15:32:12 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	n_init_spread(t_data *data, int *state, int src)
{
	int i;
	int links;
	int link;

	i = 0;
	links = data->links_num[src];
	while (i < links)
	{
		link = data->links[src][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		else if (link != data->start && link != data->end)
			state[link] = 1;
		i++;
	}
}

static	void	link_spread(t_data *d, int *depth, int src, int o_src)
{
	int i;
	int links;
	int link;

	i = 0;
	links = d->links_num[src];
	while (i < links)
	{
		link = d->links[src][i];
		if (link != -1 && link != d->end && link != d->start && link != o_src)
			if (d->bfs_state[link] == 0 || d->bfs_state[link] > *depth)
				d->bfs_state[link] = *depth;
		i++;
	}
}

static	void	n_default_spread(t_data *d, int *curr_depth, int src)
{
	int i;

	i = 0;
	while (i < d->rooms)
	{
		if (d->bfs_state[i] == *curr_depth - 1 && i != src)
			link_spread(d, curr_depth, i, src);
		i++;
	}
}

static	void	n_spread(t_data *data, int *curr_depth, int link)
{
	if (*curr_depth == 1)
		return (n_init_spread(data, data->bfs_state, link));
	return (n_default_spread(data, curr_depth, link));
}

/*
**	n_bfs runs a BFS from the room 'link' into the maze until
**	all connections to start are filled. the resulting maze state
**	is returned.
*/

int				*n_bfs(t_data *data, int link, int **s)
{
	int depth;

	if (*s == NULL)
		*s = ft_intnew(data->rooms);
	(*s)[data->start] = -999;
	(*s)[data->end] = -444;
	depth = 1;
	while (n_open_links(data, *s, data->start, link) > 0 && depth < 150)
	{
		data->bfs_state = *s;
		n_spread(data, &depth, link);
		depth++;
	}
	return (*s);
}
