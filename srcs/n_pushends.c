/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_pushends.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 16:32:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/08 16:32:16 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	n_push_ends takes a batch and pushed the room index of
**	the end node and pushes it to the front of each path.
*/

void	n_push_ends(t_list *batch, t_pathdata *p)
{
	t_list	*iter;
	int		start_val;
	t_list	*path;

	iter = batch;
	while (iter)
	{
		path = iter->content;
		start_val = *(int *)path->content;
		if (start_val != p->end)
			ft_lstpushfront(&p->end, (t_list **)&iter->content, sizeof(int *));
		iter = iter->next;
	}
}
