/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_paths.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 13:23:13 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/24 13:23:14 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int		is_next_node(t_pathdata *d, int link, int path_num, int room)
{
	if (d->bfs_data[link][1] == path_num)
	{
		if (d->bfs_data[link][0] == d->bfs_data[room][0] - 1)
		{
			if (d->bfs_data[link][0] > 0)
			{
				return (1);
			}
			return (0);
		}
		return (0);
	}
	return (0);
}

static	t_list	*map_to_path(t_pathdata *d, int room, t_list *p, int depth)
{
	int i;
	int links;
	int link;
	int path_num;

	if (room == d->start)
		return (p);
	path_num = d->bfs_data[room][1];
	ft_lstpushback(&p, &room, sizeof(int *));
	i = 0;
	links = d->links_num[room];
	while (i < links)
	{
		link = d->links[room][i];
		if (link == -1 || link == d->start)
		{
			i++;
			continue ;
		}
		if (is_next_node(d, link, path_num, room) == 1)
			return (map_to_path(d, link, p, depth + 1));
		i++;
	}
	return (p);
}

static	int		is_shortest_of_paths(t_pathdata *d, int room)
{
	int i;
	int path;
	int links;
	int link;
	int dist;

	i = 0;
	path = d->bfs_data[room][1];
	links = d->links_num[d->end];
	dist = d->bfs_data[room][0];
	while (i < links)
	{
		link = d->links[d->end][i];
		if (link != -1 && link != room && d->bfs_data[link][1] == path)
			if (d->bfs_data[link][0] < dist && d->bfs_data[link][0] > 0)
				return (0);
		i++;
	}
	return (1);
}

void			parse_paths(t_pathdata *data)
{
	int		i;
	int		links;
	int		link;
	t_list	*path;

	i = 0;
	path = NULL;
	links = data->links_num[data->end];
	while (i < links)
	{
		link = data->links[data->end][i];
		if (link == -1 || data->bfs_data[link][0] == 0 ||
			is_shortest_of_paths(data, link) == 0)
		{
			i++;
			continue ;
		}
		ft_lstpushfront(&data->end, &path, sizeof(int *));
		path = map_to_path(data, link, path, 1);
		ft_lstappend(&data->paths, path, sizeof(t_list *));
		path = NULL;
		i++;
	}
}
