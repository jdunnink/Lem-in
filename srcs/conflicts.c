/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conflicts.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 02:56:32 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/17 02:56:34 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int	search_dup(int cmp_val, t_list *paths)
{
	t_list *outer_iter;
	t_list *inner_iter;

	outer_iter = paths;
	while (outer_iter)
	{
		inner_iter = outer_iter->content;
		inner_iter = inner_iter->next;
		while (inner_iter)
		{
			if (*(int *)inner_iter->content == cmp_val)
				return (1);
			inner_iter = inner_iter->next;
		}
		outer_iter = outer_iter->next;
	}
	return (0);
}

int			conflicts(t_list *paths, int *conflict)
{
	t_list	*iter;
	int		curr_val;

	iter = paths->content;
	while (iter)
	{
		curr_val = *(int *)iter->content;
		if (search_dup(curr_val, paths->next) == 1)
		{
			*conflict = curr_val;
			return (1);
		}
		iter = iter->next;
	}
	return (0);
}
