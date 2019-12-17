/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_ants.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 21:18:37 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:46:45 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	move_swarm(t_data *data)
{
	t_list	*iter;
	t_ant	*curr;

	iter = data->active_ants;
	while (iter)
	{
		curr = iter->content;
		if (curr->has_moved == 0)
			move_ant(data, curr);
		iter = iter->next;
	}
	exit_ants(data);
}
