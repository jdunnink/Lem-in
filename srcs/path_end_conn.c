/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_end_conn.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 16:56:59 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/04 16:57:00 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	path_end_conn(t_pathdata *data, int path)
{
	int end_conns;
	int link;
	int links;
	int i;

	i = 0;
	end_conns = 0;
	links = data->links_num[data->end];
	while (i < links)
	{
		link = data->links[data->end][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (data->bfs_data[link][1] == path)
			end_conns++;
		i++;
	}
	return (end_conns);
}
