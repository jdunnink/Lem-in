/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_bfs_data.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 16:37:22 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/04 16:37:22 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int		get_start_room(t_pathdata *data, int path)
{
	int i;
	int links;
	int link;

	i = 0;
	links = data->links_num[data->start];
	while (i < links)
	{
		link = data->links[data->start][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (data->bfs_data[link][1] == path)
			return (link);
		i++;
	}
	return (-1);
}

static	void	clear_bfs_state(t_pathdata *data)
{
	int i;

	i = 0;
	while (i < data->rooms)
	{
		data->bfs_data[i][0] = 0;
		data->bfs_data[i][1] = 0;
		i++;
	}
}

void			reset_bfs_data(t_data *main, t_pathdata *data)
{
	int last_finished;
	int room;

	last_finished = *(int *)data->finish_order->content;
	room = get_start_room(data, last_finished);
	if (room == -1)
		error_exec(25, main, data);
	block_link(main, room);
	filter_deadends(&main);
	clear_bfs_state(data);
	ft_lstdel(&data->finish_order, &ft_del);
	data->total_paths = 0;
	data->path_threshold -= 1;
	data->finish_order = NULL;
}
