/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_maze.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 08:30:10 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/08 17:02:12 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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

static	int		eval_start_conn_phero(t_pathdata *data)
{
	int links;
	int i;
	int link_to_start;

	i = 0;
	links = data->links_num[data->start];
	while (i < links)
	{
		link_to_start = data->links[data->start][i];
		i++;
		if (data->pheromone[link_to_start] < 0)
			return (0);
	}
	return (1);
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
		if (eval_start_conn_phero(data) == 1 && data->path_threshold > 10)
			break ;
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
	free_backup(backup);
}
