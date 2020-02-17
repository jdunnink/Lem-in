/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traverse_maze.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 23:20:41 by jdunnink       #+#    #+#                */
/*   Updated: 2020/02/16 13:47:20 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	parse_path(t_data *data, t_list *path, int path_index)
{
	t_list *iter;
	t_list *trail;
	int		room;

	trail = path;
	iter = path->next;
	while (iter)
	{
		room = *(int *)iter->content;
		if(data->state[room] != 0)
			n_move(data, room, *(int *)trail->content, path_index);
		trail = iter;
		iter = iter->next;
	}
}

static	void	parse_paths(t_data *data, t_list *paths)
{
	t_list *iter;
	int		path_index;

	iter = paths;
	path_index = 0;
	while (iter)
	{
		parse_path(data, iter->content, path_index);
		iter = iter->next;
		path_index++;
	}
}

/*
//	execute path traversal
*/

void			traverse_maze(t_data *data, t_pathdata *path_data)
{
	data->ant_distr = ft_intnew((int)ft_listlen(path_data->paths));
	add_start_rooms(data->start, path_data->paths);
	distribute_ants(data->ants, path_data->paths, data->ant_distr);
	data->state[data->start] = 1;
	while (data->state[data->end] != data->ants)
	{
		parse_paths(data, path_data->paths);
		print_move_list(data);
		ft_lstdel(&data->move_list, &ft_del);
	}
}