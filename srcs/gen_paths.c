/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gen_paths.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 11:26:59 by jdunnink       #+#    #+#                */
/*   Updated: 2020/02/12 17:48:37 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	gen_paths calls the functions needed to find
**	the best combination of paths through the maze.
*/

int	gen_paths(t_data *data, t_pathdata *data_path)
{
	t_list *paths_l3;
	t_list *no_end;
	t_list *no_end2;

	no_end = NULL;
	no_end2 = NULL;
	paths_l3 = NULL;
	if (n_conn(data, data->end, data->start) == 1)
	{
		no_end = ft_lstnew(&data->end, sizeof(int *));
		ft_lstappend(&no_end2, no_end, sizeof(t_list *));
		data_path->total_paths = ft_listlen(no_end2);
		data_path->paths = no_end2;
		return (1);
	}
	n_find(data, &paths_l3);
	if (ft_listlen(paths_l3) == 0)
		error_exec(666, data, data_path);
	n_split_cycles(data, &paths_l3);
	n_sort(&paths_l3);
	return (n_alt_solve(data->ants, paths_l3, data_path));
}
