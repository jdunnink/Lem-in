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

static	t_link	*pop_link(t_pathdata *data)
{
	t_list *node;
	t_link *link;

	node = data->diff_override;
	data->diff_override = node->next;
	link = node->content;
	free(node);
	return (link);
}

static	int		check_override(int room, t_pathdata *data, int src)
{
	if (data->bfs_data[src][0] + 1 >= data->bfs_data[room][0])
		return (1);
	return (0);
}

static	void	exec(t_link *link, t_pathdata *data, t_list **rec, int *depth)
{
	if (check_override(link->dst, data, link->src) == 1)
	{
		purge_upstream(data, link->dst);
		if (purge_downstream(data, link->dst, depth) == 0)
			return ;
		ft_lstpushfront(&link->dst, rec, sizeof(int *));
		data->bfs_data[link->dst][0] = data->bfs_data[link->src][0] + 1;
		data->bfs_data[link->dst][1] = data->bfs_data[link->src][1];
	}
}

static	int		confirm(t_pathdata *data, t_list *record, t_link *link)
{
	int		src_p;
	int		dst_p;

	src_p = data->bfs_data[link->src][1];
	dst_p = data->bfs_data[link->dst][1];
	if (link->dst != data->start)
	{
		if (ft_lstcontains(record, link->src) == 0)
		{
			if (path_end_conn(data, src_p) <= path_end_conn(data, dst_p))
			{
				return (1);
			}
			return (0);
		}
		return (0);
	}
	return (0);
}

void			diff_override(t_pathdata *data, int *depth)
{
	t_link	*curr;
	t_list	*record;
	int		src_p;
	int		dst_p;

	record = NULL;
	while (data->diff_override != NULL)
	{
		curr = pop_link(data);
		src_p = data->bfs_data[curr->src][1];
		dst_p = data->bfs_data[curr->dst][1];
		if (confirm(data, record, curr) == 1)
		{
			if (count_branches(data, src_p, *depth - 1) == 0)
				exec(curr, data, &record, depth);
			else if (path_end_conn(data, dst_p) > 1)
				exec(curr, data, &record, depth);
		}
		free(curr);
	}
	if (record != NULL)
		ft_lstdel(&record, &ft_del);
}
