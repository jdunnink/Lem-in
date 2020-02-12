/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_ants.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/09 19:05:29 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/09 19:05:29 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	exit_ants removes all ants that have reached the end
**	from the active_ants list.
*/

void	exit_ants(t_data *data)
{
	t_list	*iter;
	t_ant	*ant;

	iter = data->active_ants;
	while (iter)
	{
		ant = iter->content;
		if (ant->room == data->end)
		{
			exit_ant(ant, data);
			if (data->active_ants == NULL)
				return ;
			iter = data->active_ants;
		}
		else
			iter = iter->next;
	}
}
