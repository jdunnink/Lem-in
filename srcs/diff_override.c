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

/*

static	void	show_end_conn(t_pathdata *data)
{
	int i;
	int links;
	int	link;

	links = data->links_num[data->end];
	i = 0;
	while (i < links)
	{
		link = data->links[data->end][i];
		printf("	link %i has path %i with distance %i\n", link, data->bfs_data[link][1], data->bfs_data[link][0]);
		i++;
	}
}

*/

static	int	contains(t_list *list, int value)
{
	t_list *iter;
	int		val;

	iter = list;
	while (iter)
	{
		val = *(int *)iter->content;
		if (val == value)
			return (1);
		iter = iter->next;
	}
	return (0);
}

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
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (data->bfs_data[link][1] == data->bfs_data[room][1])				// linked room is of the same path
		{
			if (in_range(data->bfs_data[link][0], data->bfs_data[room][0] - 1, data->bfs_data[room][0] + 1) == 1)	// linked room is of the same branch
				data->bfs_data[link][2] -= 1;								// decrease link_num of this room
		}
		i++;
	}
}

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
		if (data->bfs_data[i][1] == data->bfs_data[room][1])
		{
			if (data->bfs_data[i][0] <= data->bfs_data[room][0])
				down_streams++;
		}
		i++;
	}
//	printf("	%i downstreams found\n", down_streams);
	return (down_streams);
}

static	void	clear_upstream(t_pathdata *data, int room)
{
	int i;
	int links;
	int	link;
	int	upstream_val;
	int	path;

	if (is_convergence(data, room) != 0)
	{
		printf("	convergence found at room %i --> multiple downstreams\n", room);
		return ;
	}

	printf("		clearing upstream in room %i (%i, %i, %i)\n", room, data->bfs_data[room][0], data->bfs_data[room][1], data->bfs_data[room][2]);

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
		if (link == data->end)
		{
			printf("	upstream was part of a connection to end!\n");
		}
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (data->bfs_data[link][0] == upstream_val && data->bfs_data[link][1] == path)
		{
			printf("		more upstream found at room %i (%i, %i, %i)\n", link, data->bfs_data[link][0], data->bfs_data[link][1], data->bfs_data[link][2]);
			clear_upstream(data, link);
		}
		i++;
	}
}

static	int	find_max_depth(t_pathdata *data, int path)
{
	int max;
	int i;

	i = 0;
	max = 0;
	while (i < data->rooms)
	{
		if (data->bfs_data[i][1] == path)
		{
			if (data->bfs_data[i][0] > max)
				max = data->bfs_data[i][0];
		}
		i++;
	}
	printf("			path %i has a current max depth of %i\n", path, max);
	return (max);
}

//	if a path has reached end on a branch --> other longer branches of the same path can be overridden

static	int	count_branches(t_pathdata *data, int path, int depth)
{
	int i;
	int	branches;

	branches = 0;
	i = 0;
	while (i < data->rooms)
	{
		if (data->bfs_data[i][1] == path)
		{
			if (data->bfs_data[i][0] == depth)
				branches++;
		}
		i++;
	}
	printf("			path %i has %i branches remaining at depth %i\n", path, branches, depth);
	return (branches);
}

static	int	end_conns(t_pathdata *data, int path)
{
	int i;
	int links;
	int link;
	int	end_conns;

	end_conns = 0;
	i = 0;
	links = data->links_num[data->end];
	while (i < links)
	{
		link = data->links[data->end][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (data->bfs_data[link][1] == path)
		{
			if (data->bfs_data[link][0] > 0)
				end_conns++;
		}
		i++;
	}
	printf("			path %i has %i connections to end\n", path, end_conns);
	return (end_conns);
}

static	int	upstreams(t_pathdata *data, int room)
{
	int i;
	int links;
	int link;
	int	upstreams;

	i = 0;
	upstreams = 0;
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
			if (data->bfs_data[link][0] == data->bfs_data[room][0] + 1)
				upstreams++;
		}
		i++;
	}
	return (upstreams);
}

static	int check_branches(t_pathdata *data, int path, int hostile_path, int src_depth)
{
	int depth;
	int	branches;
	int	src_branches;
	int ret;

	printf("			checking if branch can be cut off...\n");

	depth = find_max_depth(data, hostile_path);
	ret = 1;
	branches = count_branches(data, hostile_path, depth);
	if (depth > src_depth)
		ret = 0;
//	if (branches > 1)
//		return (0);
	src_branches = branches + end_conns(data, hostile_path);

	depth = find_max_depth(data, path);
	branches = count_branches(data, path, depth) + end_conns(data, path);
	if (ret == 0)
		return (0);
	if (src_branches == branches && src_branches == 1)
	{
		printf("	conflict between two main branches! --> no override possible\n");
		return (1);
	}
	if (branches > 1 && src_branches == 1)
		return (1);
	return (0);
}

static	void	show_room_streams(t_pathdata *data, int room)
{
	int i;
	int links;
	int link;
//	ft_putchar('\n');
//	printf("		showing source streams for room %i (%i, %i, %i)\n", room, data->bfs_data[room][0], data->bfs_data[room][1], data->bfs_data[room][2]);

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
			if (data->bfs_data[link][0] == data->bfs_data[room][0] + 1)
			{
//				printf("		override source has an upstream at room %i (%i, %i, %i)\n", link, data->bfs_data[link][0], data->bfs_data[link][1], data->bfs_data[link][2]);
			}
//			else if (data->bfs_data[link][0] == data->bfs_data[room][0] - 1)
//				printf("		override source has a downstream at room %i (%i, %i, %i)\n", link, data->bfs_data[link][0], data->bfs_data[link][1], data->bfs_data[link][2]);
		}
		i++;
	}
//	ft_putchar('\n');
}

static	int	check_override(int room, t_pathdata *data, int src)
{
	int i;
	int total_links;
	int	link;

	if (room == data->start)
		return (0);

	show_room_streams(data, src);

	if (data->bfs_data[room][2] == 1)
	{
		printf("	target room % i has become a dead end --> overriding\n", room);
		return (1);
	}
	if (upstreams(data, room) == 0 && data->bfs_data[src][0] > data->bfs_data[room][0])
	{
		printf("	target room %i has lower distance and no upstreams --> overriding\n", room);
		return (1);
	}

	i = 0;
	total_links = data->links_num[room];
	while (i < total_links)
	{
		link = data->links[room][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (link == data->start)
			return (0);
		if (data->bfs_data[link][1] == data->bfs_data[room][1])				// linked room is of the same path
		{
			if (data->bfs_data[link][0] == data->bfs_data[room][0] - 1)	// linked room is downstream the same branch
			{
//				printf("		override target has a downstream at room %i (%i, %i, %i)\n", link, data->bfs_data[link][0], data->bfs_data[link][1], data->bfs_data[link][2]);
				if (data->bfs_data[link][2] <= 2)							// linked room would be cut off
				{
					printf("		cut-off danger at room %i (%i, %i, %i)\n", link, data->bfs_data[link][0], data->bfs_data[link][1], data->bfs_data[link][2]);			
					ft_putchar('\n');
					return (check_branches(data, data->bfs_data[link][1], data->bfs_data[src][1], data->bfs_data[src][0]));
				}	
			}
			else if (data->bfs_data[link][0] == data->bfs_data[room][0] + 1)
			{
//				printf("		override target has an upstream at room %i (%i, %i, %i)\n", link, data->bfs_data[link][0], data->bfs_data[link][1], data->bfs_data[link][2]);
			}
		}
		i++;
	}
	ft_putchar('\n');
	return (check_branches(data, data->bfs_data[room][1], data->bfs_data[src][1], data->bfs_data[src][0]));
}

static	void	exec_override(int dst, int src, t_pathdata *data, t_list **overridden)
{
//	if (data->bfs_data[dst][0] >= data->bfs_data[src][0] + 1)				// if target distance is higher or equal than src distance + 1
//	{
//		printf("		target distance is higher than src --> no override possible\n");
//
//		data->bfs_data[src][2] -= 1;
//		return ;
//	}
	if (check_override(dst, data, src) == 1 && is_convergence(data, dst) == 0)							// check if dest can be overridden safely
	{
		clear_upstream(data, dst);
		ft_lstpushfront(&dst, overridden, sizeof(int *));
		printf("		overriding room %i from (%i, %i, %i) to (%i, %i, %i)\n", 
				dst, data->bfs_data[dst][0], data->bfs_data[dst][1], data->bfs_data[dst][2],
				data->bfs_data[src][0] + 1, data->bfs_data[src][1], data->links_num[dst]);
		decr_conns(dst, data);
		data->bfs_data[dst][0] = data->bfs_data[src][0] + 1;							// set dist in target + 1 than src
		data->bfs_data[dst][1] = data->bfs_data[src][1];									// path is same as src
		data->bfs_data[dst][2] = data->active_links_num[dst];									// links is reinitialized and adjusted in the next round
	}
	else
	{
		printf("		could not override room %i to path %i --> would cause cut-off\n", dst, data->bfs_data[src][1]);
		if (dst != data->start)
			data->bfs_data[src][2] -= 1;
	}
}

void	diff_override(t_pathdata *data)
{
	t_link *curr;
	t_list	*overridden;

	overridden = NULL;
	while (data->diff_override != NULL)
	{
		curr = pop_link(data);

		if (curr->dst != data->start)
		{
			printf("\n	checking hostile override from room %i (%i, %i, %i) to room %i (%i, %i, %i)\n", 
				curr->src, data->bfs_data[curr->src][0], data->bfs_data[curr->src][1], data->bfs_data[curr->src][2],
				curr->dst, data->bfs_data[curr->dst][0], data->bfs_data[curr->dst][1], data->bfs_data[curr->dst][2]);
			if (contains(overridden, curr->src) == 0)
				exec_override(curr->dst, curr->src, data, &overridden);
		}
		free(curr);
	}
	if (overridden != NULL)
		ft_lstdel(&overridden, &ft_del);
}