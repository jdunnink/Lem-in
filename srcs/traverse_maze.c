/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traverse.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 23:20:41 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:44:37 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	spawn_ants(t_data *data)
{
	int i;

	i = 0;
	while (i < data->ants)
	{
		spawn_ant(data);
		i++;
	}
}

/*
**	traverse_maze takes the path solution provided
**	and sends the ants through the maze by giving each ant
**	a target route from the batch stored in data->paths.
**	moves performed by the ants are stored in the move_list
**	and printed to the standard output
*/

void			traverse_maze(t_data *data, t_pathdata *path_data)
{
	spawn_ants(data);
	assign_routes(data, path_data);
	while (data->ants_at_end != data->ants)
	{
		if (moves(data->active_ants) > 0)
			move_swarm(data);
		print_move_list(data);
		if (data->move_list != NULL)
			ft_lstdel(&(data->move_list), &ft_del);
		if (data->active_ants != NULL)
			recharge_ants(data->active_ants);
	}
	if (data->active_ants != NULL)
		error_exec(1, data, path_data);
}
