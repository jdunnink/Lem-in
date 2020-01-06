/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_maze.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 08:30:10 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/10 08:30:10 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

static	void	adjust_maze_state(t_pathdata *data, int conflict)
{
	int i;

	printf("	conflict found at %i\n", conflict);

	i = 0;
	free_paths(data);
	data->total_paths = 0;
	while (i < data->rooms)
	{
		if (i != data->start && i != data->end)
		{
			if (data->pheromone[i] > 13000 || data->pheromone[i] < 0.00)
				data->pheromone[i] = 0;
		}
		i++;
	}
	data->pheromone[conflict] = 18000;
}

void			search_maze(t_pathdata *data)
{
	int conflict;
	int i;

//	printf("	search maze is called..\n looking for path threshold: %i\n", data->path_threshold);

	i = 0;
	create_phero_trail(data);
//	printf("	phero trail set..\n");
	while (data->total_paths < data->path_threshold)
	{
		if (send_explore_wave(data) == 0)
			break ;
		spread_pheromones(data);
		recharge_ants(data->active_ants);
	}
	if (data->active_ants != NULL)
		ft_lstdel(&data->active_ants, &del_ant);
	conflict = 0;
	if (conflicts(data->paths, &conflict) != 0 && data->path_threshold < 4)
	{
		adjust_maze_state(data, conflict);
		search_maze(data);
	}
	else if (conflict != 0)
		filter_dups(data);
//	printf("	path threshold is reached! rooms: %i links: %i path collection: \n", data->rooms, data->total_links);
//	show_paths(data->paths);
}
