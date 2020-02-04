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

static	int	is_upconvergence(t_pathdata *data, int room)
{
	int i;
	int links;
	int	link;
	int up_streams;

	links = data->links_num[room];
	up_streams = 0;
	i = 0;
	while (i < links)
	{
		link = data->links[room][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (link == data->end)
			up_streams++;
		if (data->bfs_data[link][1] == data->bfs_data[room][1])
		{
			if (data->bfs_data[link][0] >= data->bfs_data[room][0]  && data->bfs_data[link][0] > 0)
				up_streams++;
		}
		i++;
	}
	return (up_streams);
}

static	int	clear_downstream(t_pathdata *data, int room, int orig_depth)
{
	int i;
	int links;
	int	link;
	int	downstream_val;
	int	path;
	int ret;

	if (is_upconvergence(data, room) > 0)
		return (1);
	if (data->bfs_data[room][0] == 1)
	{
		reconstruct_path(data, room, orig_depth, 1, data->bfs_data[room][1]);
		return (0);
	}

	i = 0;
	ret = 0;
	links = data->links_num[room];
	downstream_val = data->bfs_data[room][0] - 1;
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
		if (data->bfs_data[link][0] == downstream_val && data->bfs_data[link][1] == path && data->bfs_data[link][0] > 0)
			ret = clear_downstream(data, link, orig_depth);
		i++;
	}
	return (ret);
}

int 	purge_downstream(t_pathdata *data, int room, int *curr_depth)
{
	int i;
	int links;
	int link;
	int	room_path;
	int room_dis;
	int	ret;
	
	if (data->bfs_data[room][0] == 1)
	{
		if (is_upconvergence(data, room) > 0)
			return (1);
		reconstruct_path(data, room, *curr_depth - 1, 1, data->bfs_data[room][1]);
		return (0);
	}
	i = 0;
	ret = 0;
	links = data->links_num[room];
	room_path = data->bfs_data[room][1];
	room_dis = data->bfs_data[room][0];
	data->bfs_data[room][0] = 0	;		
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
		if (data->bfs_data[link][1] == room_path)
		{
			if (data->bfs_data[link][0] < room_dis && data->bfs_data[link][0] > 0)
				ret = clear_downstream(data, link, (*curr_depth) - 1);
		}
		i++;
	}
	return (ret);
}
