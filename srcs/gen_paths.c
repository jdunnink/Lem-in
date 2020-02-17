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

	paths_l3 = NULL;
	n_find(data, &paths_l3);
	if (ft_listlen(paths_l3) == 0)
		error_exec(666, data, data_path);
	n_split_cycles(data, &paths_l3);
	n_sort(&paths_l3);
	return (n_alt_solve(data->ants, paths_l3, data_path));
}
