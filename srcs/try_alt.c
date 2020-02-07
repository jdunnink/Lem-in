/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   try_alt.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 11:26:59 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/07 11:27:00 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

int	try_alt(t_data *d, t_pathdata *p)
{
	t_list *paths_l3;

//	printf("	try alt is called\n");

	paths_l3 = NULL;
//	printf("	finding paths..\n");
	n_find(d, &paths_l3);
//	printf("	splittin cycles\n");
	n_split_cycles(d, &paths_l3);
//	printf("	sorting...\n");
	n_sort(&paths_l3);
	return (n_alt_solve(paths_l3, p));
}