/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_solve.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 11:50:37 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/06 11:50:38 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

static	int	n_batch_has_value(int value, t_list *paths_l2)
{
	t_list *iter;

	iter = paths_l2;
	while (iter)
	{
		if (ft_lstcontains(iter->content, value) == 1)
			return (1);
		iter = iter->next;
	}
	return (0);
}

static	int	n_conflict(t_list *new, t_list *paths_l2)
{
	t_list *iter;

	iter = new;
	while (iter)
	{
		if (n_batch_has_value(*(int *)iter->content, paths_l2) == 1)
			return (1);
		iter = iter->next;
	}
	return (0);
}

int	n_solve(t_list *paths_l3, t_pathdata *p)
{
	int threshold;
	int paths;
	t_list	*path_buff;

	printf("	all collected paths: \n");
	n_dump_paths(paths_l3);

	exit (0);

	threshold = ft_listlen(paths_l3);
	printf("	solver is looking for a combination of %i paths\n", threshold);

	path_buff = NULL;
	paths = 0;
	while (paths < threshold)
	{
//		if (n_add_path(&path_buff, paths_l3) == 0)
//		{
//			paths = 0;
//			threshold--;
//		}
//		else
			paths++;
		printf("	%i paths collected	\n", paths);
		show_paths(path_buff);
	}

	printf("	solution: \n");
	show_paths(path_buff);


	exit (0);
	return (0);
}