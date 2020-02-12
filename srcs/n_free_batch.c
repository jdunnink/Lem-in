/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_free_batch.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 15:44:53 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/10 15:44:54 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	n_free_batch takes a pointer to a batch of paths
**	and frees each path in the batch, as well as
**	the batch-level linked list
*/

void	n_free_batch(t_list *batch)
{
	t_list *iter;

	iter = batch;
	if (iter == NULL)
		return ;
	while (iter)
	{
		if (iter->content != NULL)
		{
			ft_lstdel((t_list **)&iter->content, &ft_del);
			iter->content = NULL;
		}
		iter = iter->next;
	}
	ft_lstdel(&batch, &ft_del);
}
