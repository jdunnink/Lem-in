/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   try_normal.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 14:41:17 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/05 14:41:18 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	try_normal(t_data *d, t_pathdata *p)
{
	t_list *paths_l3;

	paths_l3 = NULL;
	n_find(d, &paths_l3);
	n_split_cycles(d, &paths_l3);
	n_sort(&paths_l3);
	return (n_solve(paths_l3, p));
}
