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

	i = 0;
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

static	void	take_backup(t_list *backup, t_pathdata *data)
{
	free_paths(data);
	data->paths = backup;
}

static	void	init_backup(t_list **backup, t_pathdata *data)
{
	*backup = NULL;
	if (data->paths != NULL)
	{
		create_backup(data->paths, backup);
		show_paths(*backup);
		free_paths(data);
		data->paths = NULL;
	}
}

static	int		check_backup(t_list *backup, t_pathdata *data)
{
	if (backup != NULL)
	{
		take_backup(backup, data);
		return (1);
	}
	return (0);
}

void			search_maze(t_pathdata *data)
{
	int		conflict;
	t_list	*backup;

	init_backup(&backup, data);
	create_phero_trail(data);
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
		if (check_backup(backup, data) == 1)
			return ;
		adjust_maze_state(data, conflict);
		return (search_maze(data));
	}
	else if (conflict != 0)
		filter_dups(data);
	free_backup(backup);
}
