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

#include <stdio.h>

static	int	is_convergence(t_pathdata *data, int room)
{
	int i;
	int links;
	int	link;
	int down_streams;

	links = data->links_num[room];
	down_streams = 0;
	i = 0;
	while (i < links)
	{
		link = data->links[room][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (data->bfs_data[link][1] == data->bfs_data[room][1])
		{
			if (data->bfs_data[link][0] <= data->bfs_data[room][0] && data->bfs_data[link][0] > 0)
				down_streams++;
		}
		i++;
	}
//	printf("			%i downstreams found\n", down_streams);
	return (down_streams);
}

static	void	clear_upstream(t_pathdata *data, int room)
{
	int i;
	int links;
	int	link;
	int	upstream_val;
	int	path;

//	printf("		clearing upstream in room %i (%i, %i, %i)\n", room, data->bfs_data[room][0], data->bfs_data[room][1], data->bfs_data[room][2]);

	if (is_convergence(data, room) > 1)
	{
//		printf("	convergence found at room %i --> %i downstreams\n", room, is_convergence(data, room));
		return ;
	}


	i = 0;
	links = data->links_num[room];
	upstream_val = data->bfs_data[room][0] + 1;
	path = data->bfs_data[room][1];
	data->bfs_data[room][0] = 0;
	data->bfs_data[room][1] = 0;
	data->bfs_data[room][2] = 0;
	while (i < links)
	{
		link = data->links[room][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (link == data->end)
		{
//			printf("	upstream was part of a connection to end!\n");
		}

		if (data->bfs_data[link][0] == upstream_val && data->bfs_data[link][1] == path && data->bfs_data[link][0] > 0)
		{
//			printf("		more upstream found at room %i (%i, %i, %i)\n", link, data->bfs_data[link][0], data->bfs_data[link][1], data->bfs_data[link][2]);
			clear_upstream(data, link);
		}
		i++;
	}
}

void	purge_upstream(t_pathdata *data, int room)
{
	int i;
	int links;
	int link;

//	printf("		purging upstream in room %i (%i, %i, %i)\n", room, data->bfs_data[room][0], data->bfs_data[room][1], data->bfs_data[room][2]);

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
		if (data->bfs_data[link][1] == data->bfs_data[room][1])
		{
			if (data->bfs_data[link][0] > data->bfs_data[room][0] && data->bfs_data[link][0] > 0)
				clear_upstream(data, link);
		}
		i++;
	}
}
