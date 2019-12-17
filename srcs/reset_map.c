/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 18:23:28 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/11 18:23:30 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	reset_map(t_data *data)
{
	int		*state;
	float	*pheromone;
	int		i;

	i = 0;
	pheromone = data->pheromone;
	state = data->state;
	while (i < data->rooms)
	{
		pheromone[i] = 0;
		state[i] = 0;
		i++;
	}
	state[data->start] = data->ants_at_start;
	pheromone[data->start] = state[data->start] * 0.000001;
}
