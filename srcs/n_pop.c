/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_pop.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 16:28:50 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/08 16:28:51 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	n_pop returns the first path contained in the batch
**	passed as paramenter. The path pointer in the batch is stored as
**	as well, which is set to NULL, once the path is moved to another
**	batch.
*/

t_list	*n_pop(t_list *batch, t_list ***ptr)
{
	t_list *iter;

	iter = batch;
	while (iter)
	{
		if (iter->content != NULL)
		{
			*ptr = (t_list **)&iter->content;
			return (iter->content);
		}
		iter = iter->next;
	}
	return (NULL);
}
