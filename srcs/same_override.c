/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   same_override.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 18:20:56 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/20 18:21:06 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

static	t_link *pop_link(t_pathdata *data)
{
	t_list *node;
	t_link *link;

	node = data->same_override;
	data->same_override = node->next;
	link = node->content;
	free(node);
	return (link);
}

static	int	in_range(int num, int floor, int ceil)
{
	if (num >= floor && num <= ceil)
		return (1);
	return (0);
}

static	void exec_override(int dst, int src, t_pathdata *data)
{
	int dst_dis;
	int src_dis;

	dst_dis = data->bfs_data[dst][0];
	src_dis = data->bfs_data[src][0];
	if (dst_dis == src_dis)
		data->bfs_data[src][2] -= 1;
	else if (in_range(dst_dis, src_dis - 1, src_dis + 1) == 0)
		data->bfs_data[src][2] -= 1;
	else
	{
		printf("	path: %i --> same_override was called from room %i to target room %i --> rooms are connected on the same branch\n", data->bfs_data[dst][1], src, dst);
		return ;
	}
	printf("	path: %i --> same_override was called from room %i to target room %i --> rooms are from different branches --> decremented link_count of %i to %i\n", data->bfs_data[dst][1], src, dst, src, data->bfs_data[src][0]);
}

void	same_override(t_pathdata *data)
{
	ft_putchar('\n');
	t_link *curr;

	while (data->same_override != NULL)
	{
		curr = pop_link(data);
		exec_override(curr->dst, curr->src, data);
		free(curr);
	}
	ft_putchar('\n');
}