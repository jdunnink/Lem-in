/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_new_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 11:57:30 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/06 11:57:31 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int	n_lstcmp(t_list *one, t_list *two)
{
	if (ft_listlen(one) != ft_listlen(two))
		return (0);
	while (one)
	{
		if (*(int *)one->content != *(int *)two->content)
			return (0);
		one = one->next;
		two = two->next;
	}
	return (1);
}

/*
**	n_new_path checks if a path (new) is a unique
**	path that is not already in the batch passed
**	as parameter. returns 1 if unique, 0 if not.
*/

int			n_new_path(t_list *new, t_list **batch)
{
	t_list *iter;

	iter = *batch;
	while (iter)
	{
		if (n_lstcmp(new, iter->content) == 1)
			return (0);
		iter = iter->next;
	}
	return (1);
}
