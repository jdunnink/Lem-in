/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   adjust_maze_state.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 16:24:05 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/10 16:24:06 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	adjust_maze_state(t_pathdata *data, int conflict)
{
	int i;

	i = 0;
	data->total_paths = 0;
	while (i < data->rooms)
	{
		if (i != data->start && i != data->end)
		{
			if (data->pheromone[i] > 13000 || data->pheromone[i] < 0.00)
				if (data->pheromone[i] < 17999)
					data->pheromone[i] = 0;
		}
		i++;
	}
	data->pheromone[conflict] = 18000;
}
