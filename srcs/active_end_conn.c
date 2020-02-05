/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   active_end_conn.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 09:46:17 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/05 09:46:25 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	active_end_conn(t_pathdata *data)
{
	int i;
	int links;
	int	link;
	int paths;

	paths = 0;
	links = data->links_num[data->end];
	i = 0;
	while (i < links)
	{
		link = data->links[data->end][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (data->bfs_data[link][0] > 0)
			paths++;
		i++;
	}
	return (paths);
}
