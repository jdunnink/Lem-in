/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_phero_trail.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/16 17:55:00 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/16 17:55:08 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int		start_or_end(t_pathdata *data, int room)
{
	if (room == data->start || room == data->end)
		return (1);
	return (0);
}

static	void	mark_links(t_pathdata *data, int room, float phero)
{
	float	partial;
	int		all_links;
	int		i;
	int		link_i;

	partial = (0.95 * (phero * -1)) * -1;
	all_links = data->links_num[room];
	i = 0;
	while (i < all_links)
	{
		link_i = data->links[room][i];
		if (data->pheromone[link_i] < 10000 && start_or_end(data, link_i) == 0)
		{
			if (data->pheromone[link_i] > partial)
			{
				data->pheromone[link_i] = partial;
				data->state[link_i] = 0;
			}
		}
		i++;
	}
}

void			create_phero_trail(t_pathdata *data)
{
	int i;

	i = 0;
	while (i < data->rooms)
	{
		if (data->pheromone[i] < 0.000000 && data->state[i] == 0)
		{
			mark_links(data, i, data->pheromone[i]);
			data->state[i] = 1;
			i = 0;
		}
		i++;
	}
	i = 0;
	while (i < data->rooms)
	{
		if (i != data->start)
			data->state[i] = 0;
		i++;
	}
}
