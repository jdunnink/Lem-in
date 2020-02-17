/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_move.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 09:15:40 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/17 09:15:42 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int		n_startend(t_data *data, int path_index, int *ant_nbr)
{
	if (data->ant_distr[path_index] < 0)
		error_exec(80, data, NULL);
	if (data->ant_distr[path_index] == 0)
		return (0);
	data->state[data->end]++;
	*ant_nbr = data->state[data->start];
	data->state[data->start]++;
	data->ant_distr[path_index]--;
	return (1);
}

static	int		n_start(t_data *data, int next, int path_index, int *ant_nbr)
{
	if (data->ant_distr[path_index] < 0)
		error_exec(80, data, NULL);
	if (data->ant_distr[path_index] == 0)
		return (0);
	data->state[next] = data->state[data->start];
	*ant_nbr = data->state[next];
	data->state[data->start]++;
	data->ant_distr[path_index]--;
	return (1);
}

/*
**	move ants between rooms by adjusting the maze state
*/

void			n_move(t_data *data, int room, int next, int path_index)
{
	int ant_nbr;
	int ret;

	ret = 1;
	if (next == data->start)
		error_exec(78, data, NULL);
	else if (next != data->end && data->state[next] != 0)
		error_exec(79, data, NULL);
	ant_nbr = data->state[room];
	if (next == data->end && room == data->start)
		ret = n_startend(data, path_index, &ant_nbr);
	else if (next == data->end)
	{
		data->state[data->end]++;
		data->state[room] = 0;
	}
	else if (room == data->start)
		ret = n_start(data, next, path_index, &ant_nbr);
	else
	{
		data->state[next] = data->state[room];
		data->state[room] = 0;
	}
	if (ret == 1)
		save_move_output(ant_nbr, next, data);
}
