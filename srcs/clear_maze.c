/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear_maze.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/18 13:27:02 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/18 13:27:03 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

static	void	cleanup_phero(t_pathdata *data)
{
	int i;

//	printf("	cleaning up phero\n");

	i = 0;
	while (i < data->rooms)
	{
		if (i != data->end && i != data->start)
		{
			if (data->pheromone[i] < 14999)
				data->pheromone[i] = 0;
		}
		i++;
	}
}

static	void	reset_state(t_pathdata *data)
{
	int i;

//	printf("	resettin state\n");
	
	i = 0;
	while (i < data->rooms)
	{
		data->state[i] = 0;
		i++;
	}
}

void	clear_maze(t_pathdata *data)
{
	reset_state(data);
	if (data->active_ants != NULL)
		ft_lstdel(&data->active_ants, &del_ant);
	cleanup_phero(data);
	data->ants_at_start = data->explore_ants;
	data->ants_in_maze = 0;
	data->ants_at_end = 0;
	data->state[data->start] = data->ants_at_start;
}