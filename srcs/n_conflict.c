/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_conflict.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 16:48:34 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/06 16:48:34 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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

int	n_conflict(t_list *new, t_list *paths_l2)
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
