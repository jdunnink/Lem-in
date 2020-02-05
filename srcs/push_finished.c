/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_finished.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 16:36:07 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/04 16:36:08 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	push_finished(t_pathdata *data)
{
	int i;
	int links;
	int link;
	int path;

	i = 0;
	links = data->links_num[data->end];
	while (i < links)
	{
		link = data->links[data->end][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (data->bfs_data[link][0] > 0)
		{
			path = data->bfs_data[link][1];
			if (ft_lstcontains(data->finish_order, path) == 0)
				ft_lstpushfront(&path, &data->finish_order, sizeof(int *));
		}
		i++;
	}
}
