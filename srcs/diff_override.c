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

static	int	check_override(int room, t_pathdata *data, int src)
{
	if (data->bfs_data[src][0] + 1 >= data->bfs_data[room][0])
		return (1);
	return (0);
}

static	void	exec_override(int dst, int src, t_pathdata *data, t_list **overridden, int *curr_depth)
{
	if (check_override(dst, data, src) == 1)
	{
		purge_upstream(data, dst);
		if (purge_downstream(data, dst, curr_depth) == 0)
			return ;
		ft_lstpushfront(&dst, overridden, sizeof(int *));
		data->bfs_data[dst][0] = data->bfs_data[src][0] + 1;
		data->bfs_data[dst][1] = data->bfs_data[src][1];
		data->bfs_data[dst][2] = data->active_links_num[dst];
	}
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
			if (contains(overridden, curr->src) == 0)
			{
				if (path_end_conn(data, data->bfs_data[curr->src][1]) <= path_end_conn(data, data->bfs_data[curr->dst][1]))
				{
					if (count_branches(data, data->bfs_data[curr->src][1], *curr_depth - 1) == 0)
						exec_override(curr->dst, curr->src, data, &overridden, curr_depth);
					else if (path_end_conn(data, data->bfs_data[curr->dst][1]) > 1)
						exec_override(curr->dst, curr->src, data, &overridden, curr_depth);
				}
			}
		}
		free(curr);
	}
	if (overridden != NULL)
		ft_lstdel(&overridden, &ft_del);
}