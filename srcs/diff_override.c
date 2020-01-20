/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   diff_override.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 18:47:31 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/20 18:47:32 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

static	int	in_range(int num, int floor, int ceil)
{
	if (num >= floor && num <= ceil)
		return (1);
	return (0);
}

static	t_link *pop_link(t_pathdata *data)
{
	t_list *node;
	t_link *link;

	node = data->diff_override;
	data->diff_override = node->next;
	link = node->content;
	free(node);
	return (link);
}

static	void	decr_conns(int room, t_pathdata *data)
{
	int i;
	int total_links;
	int	link;

	i = 0;
	total_links = data->links_num[room];
	while (i < total_links)
	{
		link = data->links[room][i];
		if (data->bfs_data[link][1] == data->bfs_data[room][1])				// linked room is of the same path
		{
			if (in_range(data->bfs_data[link][0], data->bfs_data[room][0] - 1, data->bfs_data[room][0] + 1) == 1)	// linked room is of the same branch
				data->bfs_data[link][2] -= 1;								// decrease link_num of this room
		}
		i++;
	}
}

static	int	check_override(int room, t_pathdata *data)
{
	int i;
	int total_links;
	int	link;

	if (room == data->start)
		return (0);

	i = 0;
	total_links = data->links_num[room];
	while (i < total_links)
	{
		link = data->links[room][i];
		if (link == data->start)
			return (0);
		if (data->bfs_data[link][1] == data->bfs_data[room][1])				// linked room is of the same path
		{
			if (data->bfs_data[link][0] == data->bfs_data[room][0] - 1)	// linked room is of the same branch
			{
				if (data->bfs_data[link][2] <= 2)							// linked room would be cut off
				{
					printf("	cut-off danger at room %i (%i, %i, %i)\n", link, data->bfs_data[link][0], data->bfs_data[link][1], data->bfs_data[link][2]);			
					return (0);
				}		
			}
		}
		i++;
	}
	return (1);
}

static	void	exec_override(int dst, int src, t_pathdata *data)
{
	if (data->bfs_data[dst][0] >= data->bfs_data[src][0] + 1)				// if target distance is higher or equal than src distance + 1
	{
		data->bfs_data[src][2] -= 1;
		return ;
	}
	else if (check_override(dst, data) == 1)							// check if dest can be overridden safely
	{
		printf("	overriding room %i from (%i, %i, %i) to (%i, %i, %i)\n", 
				dst, data->bfs_data[dst][0], data->bfs_data[dst][1], data->bfs_data[dst][2],
				data->bfs_data[src][0] + 1, data->bfs_data[src][1], data->links_num[dst]);
		decr_conns(dst, data);
		data->bfs_data[dst][0] = data->bfs_data[src][0] + 1;							// set dist in target + 1 than src
		data->bfs_data[dst][1] = data->bfs_data[src][1];									// path is same as src
		data->bfs_data[dst][2] = data->links_num[dst];									// links is reinitialized and adjusted in the next round
	}
	else
	{
		printf("	could not override room %i to path %i --> would cause cut-off\n", dst, data->bfs_data[src][1]);
		if (dst != data->start)
			data->bfs_data[src][2] -= 1;
	}
}

void	diff_override(t_pathdata *data)
{
	t_link *curr;

	while (data->diff_override != NULL)
	{
		curr = pop_link(data);

		if (data->bfs_data[curr->src][1] != data->bfs_data[curr->dst][1] && curr->dst != data->start)
		{
//			printf("\n	checking hostile override from room %i (%i, %i, %i) to room %i (%i, %i, %i)\n", 
//				curr->src, data->bfs_data[curr->src][0], data->bfs_data[curr->src][1], data->bfs_data[curr->src][2],
//				curr->dst, data->bfs_data[curr->dst][0], data->bfs_data[curr->dst][1], data->bfs_data[curr->dst][2]);
			exec_override(curr->dst, curr->src, data);
		}

		free(curr);
	}
}