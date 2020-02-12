/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   moves.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 21:16:00 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:46:51 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	moves counts the number of ants left
**	in a list of ants that have not moved yet.
*/

int	moves(t_list *ants)
{
	t_list	*iter;
	t_ant	*curr;
	int		moves;

	moves = 0;
	iter = ants;
	while (iter)
	{
		curr = iter->content;
		if (curr->has_moved == 0)
			moves++;
		iter = iter->next;
	}
	return (moves);
}
