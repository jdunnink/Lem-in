/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   recharge_ants.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 15:25:17 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:47:29 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	recharge_ants is used to reset the has_moved
**	variable in the active ants list after all
**	ants have moved and the turn has ended.
*/

void	recharge_ants(t_list *active_ants)
{
	t_list	*iter;
	t_ant	*curr;

	iter = active_ants;
	while (iter)
	{
		curr = iter->content;
		curr->has_moved = 0;
		iter = iter->next;
	}
}
