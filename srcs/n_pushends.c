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

void	n_push_ends(t_list *batch, t_pathdata *p)
{
	t_list *iter;

	iter = batch;
	while (iter)
	{
		ft_lstpushfront(&p->end, (t_list **)&iter->content, sizeof(int *));
		iter = iter->next;
	}
}
