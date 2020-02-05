/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_maze.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 08:30:10 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/08 17:02:12 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	process_start(t_pathdata *data, int *curr_depth)
{
	int i;
	int	total_links;
	int	link;

	i = 0;
	data->bfs_data[data->start][0] = -1;
	data->bfs_data[data->start][1] = -1;
	total_links = data->links_num[data->start];
	while (i < total_links)
	{
		link = data->links[data->start][i];
		if (link != -1)
		{
			data->bfs_data[link][0] = 1;
			data->bfs_data[link][1] = i;
		}
		i++;
	}
	(*curr_depth)++;
}

static	void	set_empty(int link, int index, t_pathdata *data)
{
	data->bfs_data[link][0] = data->bfs_data[index][0] + 1;
	data->bfs_data[link][1] = data->bfs_data[index][1];
	if (data->bfs_data[link][2] == 1)
		data->bfs_data[index][2] -= 1;
}

static	void push_link(int link, int index, t_pathdata *data)
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
	while(i < total_links)
	{
		link = data->links[index][i];
		if (link != data->end && link != -1)
			set_link(link, index, data);
		i++;
	}
}

static	void	process_bfs(t_pathdata *data, int *curr_depth)
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

static	void	process_rooms(t_pathdata *data, int *curr_depth)
{
	if (*curr_depth == 1)
		process_start(data, curr_depth);
	else
		process_bfs(data, curr_depth);
}

void			search_maze(t_pathdata *data)
{
	int			curr_depth;

	curr_depth = 1;
	while (curr_depth < 100)
	{
		process_rooms(data, &curr_depth);
		push_finished(data);
		if (active_end_conn(data) == data->path_threshold)
		{
			if ((int)ft_listlen(data->finish_order) >= data->path_threshold)
				break ;
		}
	}
	parse_paths(data);
}
