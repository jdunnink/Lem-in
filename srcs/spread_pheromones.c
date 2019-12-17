/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   spread_pheromones.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 15:14:41 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:47:41 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	spread_pheromones(t_pathdata *data)
{
	int rooms;
	int i;

	rooms = data->rooms;
	i = 0;
	while (i < rooms)
	{
		if (data->state[i] != 0 && data->ants_at_end == 0)
			data->pheromone[i] += data->state[i] * 0.000001;
		i++;
	}
}
