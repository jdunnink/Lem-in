/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_branches.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 16:53:36 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/04 16:53:37 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	count_branches(t_pathdata *data, int path, int curr_depth)
{
	int i;
	int rooms;
	int branches;

	rooms = data->rooms;
	i = 0;
	branches = 0;
	while (i < rooms)
	{
		if (data->bfs_data[i][1] == path)
		{
			if (data->bfs_data[i][0] == curr_depth)
				branches++;
		}
		i++;
	}
	return (branches);
}
