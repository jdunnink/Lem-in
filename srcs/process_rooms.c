/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_rooms.c                                    :+:    :+:            */
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

void			process_rooms(t_pathdata *data, int *curr_depth)
{
	if (*curr_depth == 1)
		process_start(data, curr_depth);
	else
		process_bfs(data, curr_depth);
}
