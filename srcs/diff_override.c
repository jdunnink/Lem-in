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

static	int	has_end_conn(t_pathdata *data, int path)
{
	int i;
	int links;
	int link;

//	printf("	has end conn is called with path %i\n", path);

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
//		printf("	checking room %i (%i, %i, %i)\n", link, data->bfs_data[link][0], data->bfs_data[link][1], data->bfs_data[link][2]);
		if (data->bfs_data[link][1] == path && data->bfs_data[link][0] != 0)
			return (1);
		i++;
	}
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

static	int	check_override(int room, t_pathdata *data, int src, int *curr_depth)
{
	if (is_link_to_start(data, room) == 1)
	{
		printf("	target is connected to start\n");
		return (0);
	}

	if (data->bfs_data[src][0] + 1 >= data->bfs_data[room][0])
	{
		printf("		target distance is lower\n");
		return (1);
	}
	printf("		target distance is higher\n");
	return (0);
}

static	void	exec_override(int dst, int src, t_pathdata *data, t_list **overridden, int *curr_depth)
{
	if (check_override(dst, data, src, curr_depth) == 1)							// check if dest can be overridden safely
	{
		purge_upstream(data, dst);
		if (purge_downstream(data, dst, curr_depth) == 0)
		{
			printf("	override would cause elimination of path %i\n", data->bfs_data[dst][1]);
			return ;
		}
		ft_lstpushfront(&dst, overridden, sizeof(int *));
		printf("		overriding room %i from (%i, %i, %i) to (%i, %i, %i)\n", 
				dst, data->bfs_data[dst][0], data->bfs_data[dst][1], data->bfs_data[dst][2],
				data->bfs_data[src][0] + 1, data->bfs_data[src][1], data->links_num[dst]);
	
		data->bfs_data[dst][0] = data->bfs_data[src][0] + 1;							// set dist in target + 1 than src
		data->bfs_data[dst][1] = data->bfs_data[src][1];									// path is same as src
		data->bfs_data[dst][2] = data->active_links_num[dst];									// links is reinitialized and adjusted in the next round
	}
	else
		printf("		could not override room %i to path %i\n", dst, data->bfs_data[src][1]);
}

void	diff_override(t_pathdata *data, int *curr_depth)
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
			if (contains(overridden, curr->src) == 0 && has_end_conn(data, data->bfs_data[curr->src][1]) == 0)
			{
				printf("	source room %i has %i connections to end\n", curr->src, has_end_conn(data, data->bfs_data[curr->src][1]));
				exec_override(curr->dst, curr->src, data, &overridden, curr_depth);
			}
			else
				printf("	reverse override was already triggered\n");
		}
		free(curr);
	}
	if (overridden != NULL)
		ft_lstdel(&overridden, &ft_del);
}