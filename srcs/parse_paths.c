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

static	t_list	*map_to_path(t_pathdata *data, int room, t_list *path, int depth)
{
	int i;
	int links;
	int link;
	int path_num;

	if (room == data->start)
		return (path);
	path_num = data->bfs_data[room][1];
	ft_lstpushback(&path, &room, sizeof(int *));
	i = 0;
	links = data->links_num[room];
	while (i < links)
	{
		link = data->links[room][i];
		if (link == -1 || link == data->start)
		{
			i++;
			continue ;
		}
		if (data->bfs_data[link][1] == path_num)
		{
			if (data->bfs_data[link][0] == data->bfs_data[room][0] - 1)
			{
				if (data->bfs_data[link][0] > 0)
				{
					path = map_to_path(data, link, path, depth + 1);
					return (path);
				}
			}
		}
		i++;
	}
	return (path);
}

static	int		is_shortest_of_paths(t_pathdata *data, int room)
{
	int i;
	int path;
	int links;
	int link;
	int distance;

	i = 0;
	path = data->bfs_data[room][1];
	links = data->links_num[data->end];
	distance = data->bfs_data[room][0];
	while (i < links)
	{
		link = data->links[data->end][i];
		if (link == -1 || link == room)
		{
			i++;
			continue ;
		}
		if (data->bfs_data[link][1] == path)
		{
			if (data->bfs_data[link][0] < distance && data->bfs_data[link][0] > 0)
				return (0);
		}
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
		if (link == -1 || data->bfs_data[link][0] == 0)
		{
			i++;
			continue ;
		}
		if (is_shortest_of_paths(data, link) == 0)
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
