/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   spawn_ant.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 15:16:49 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:47:34 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	spawn_ants is used during the traversal phase
**	of the program to send ants into the maze.
*/

void	spawn_ant(t_data *data)
{
	t_ant *new_ant;

	if (data->ants_at_start == 0)
		return ;
	new_ant = (t_ant *)malloc(sizeof(t_ant));
	if (!new_ant)
		error_exec(2, data, NULL);
	new_ant->room = data->start;
	new_ant->has_moved = 0;
	new_ant->number = 0;
	new_ant->target_path = NULL;
	ft_lstappend(&(data->active_ants), new_ant, sizeof(t_ant));
}
