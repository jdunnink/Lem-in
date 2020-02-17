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
	t_list	*iter;
	t_list	*trail;
	int		room;

	trail = path;
	iter = path->next;
	while (iter)
	{
		room = *(int *)iter->content;
		if (data->state[room] != 0)
			n_move(data, room, *(int *)trail->content, path_index);
		trail = iter;
		iter = iter->next;
	}
}

static	void	parse_paths(t_data *data, t_list *paths)
{
	t_list	*iter;
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

static	void	remove_unused(t_pathdata *path_data, int *ant_distr)
{
	t_list	*new;
	t_list	*iter;
	int		i;

	new = NULL;
	iter = path_data->paths;
	i = 0;
	while (iter)
	{
		if (ant_distr[i] != 0)
		{
			ft_lstappend(&new, iter->content, sizeof(t_list *));
			iter->content = NULL;
		}
		else
		{
			ft_lstdel((t_list **)&iter->content, &ft_del);
			iter->content = NULL;
		}
		iter = iter->next;
		i++;
	}
	ft_lstdel(&path_data->paths, &ft_del);
	path_data->paths = new;
}

/*
**	execute path traversal
*/

void			traverse_maze(t_data *data, t_pathdata *path_data)
{
	data->ant_distr = ft_intnew((int)ft_listlen(path_data->paths));
	add_start_rooms(data->start, path_data->paths);
	distribute_ants(data->ants, path_data->paths, data->ant_distr);
	remove_unused(path_data, data->ant_distr);
	data->state[data->start] = 1;
	while (data->state[data->end] != data->ants)
	{
		parse_paths(data, path_data->paths);
		print_move_list(data);
		ft_lstdel(&data->move_list, &ft_del);
	}
}
