/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_bfs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 09:57:22 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/05 09:57:24 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	set_empty(int link, int index, t_pathdata *data)
{
	data->bfs_data[link][0] = data->bfs_data[index][0] + 1;
	data->bfs_data[link][1] = data->bfs_data[index][1];
	if (data->bfs_data[link][2] == 1)
		data->bfs_data[index][2] -= 1;
}

static	void	push_link(int link, int index, t_pathdata *data)
{
	t_link conn;

	conn.src = index;
	conn.dst = link;
	if (data->bfs_data[link][1] != data->bfs_data[index][1])
		ft_lstpushfront(&conn, &data->diff_override, sizeof(t_link *));
}

static	void	set_link(int link, int index, t_pathdata *data)
{
	int link_dis;

	link_dis = data->bfs_data[link][0];
	if (link_dis == 0)
		set_empty(link, index, data);
	else
		push_link(link, index, data);
}

static	void	set_room(int index, t_pathdata *data)
{
	int i;
	int	total_links;
	int	link;

	i = 0;
	total_links = data->links_num[index];
	while (i < total_links)
	{
		link = data->links[index][i];
		if (link != data->end && link != -1)
			set_link(link, index, data);
		i++;
	}
}

void			process_bfs(t_pathdata *data, int *curr_depth)
{
	int i;

	i = 0;
	while (i < data->rooms)
	{
		if (data->bfs_data[i][0] == (*curr_depth) - 1 && i != data->end)
			set_room(i, data);
		i++;
	}
	(*curr_depth)++;
	diff_override(data, curr_depth);
}
