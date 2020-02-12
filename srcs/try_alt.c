/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   try_alt.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 11:26:59 by jdunnink       #+#    #+#                */
/*   Updated: 2020/02/11 16:02:36 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	try_alt calls the functions needed to find
**	the best combination of paths through the maze.
*/

int	try_alt(t_data *d, t_pathdata *p)
{
	t_list *paths_l3;

	paths_l3 = NULL;
	n_find(d, &paths_l3);
	n_split_cycles(d, &paths_l3);
	n_sort(&paths_l3);
	if (ft_listlen(paths_l3) == 0)
		error_exec(666, d, p);
	return (n_alt_solve(d->ants, paths_l3, p));
}
