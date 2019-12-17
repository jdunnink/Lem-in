/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_ant.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 15:21:45 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:46:31 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	save_move_output(t_ant *ant, int next_room, t_data *data)
{
	char	*move_output;
	char	*ant_number;
	char	*room_name;

	ant_number = ft_itoa(ant->number);
	room_name = get_room_name(next_room, data);
	move_output = ft_strjoin_free("L", ant_number, 2);
	move_output = ft_strjoin_free(move_output, "-", 1);
	move_output = ft_strjoin_free(move_output, room_name, 1);
	ft_lstappend(&(data->move_list), move_output, sizeof(char *));
}

static	void	move_to_room(t_data *data, t_ant *ant, int next_room)
{
	if (ant->room == data->start && ant->number == 0)
	{
		(data->ants_at_start)--;
		(data->ants_in_maze)++;
		ant->number = (data->ants - data->ants_at_start);
	}
	if (next_room == data->end)
	{
		(data->ants_in_maze)--;
		(data->ants_at_end)++;
	}
	save_move_output(ant, next_room, data);
	data->state[ant->room]--;
	data->state[next_room]++;
	ant->has_moved = 1;
	ant->room = next_room;
}

void			move_ant(t_data *data, t_ant *ant)
{
	t_list	*iter;
	int		next_room;

	iter = ant->target_path;
	while (iter->next)
		iter = iter->next;
	next_room = *(int *)iter->content;
	if (data->state[next_room] == 0 || next_room == data->end)
	{
		ft_lstdelend(&ant->target_path);
		move_to_room(data, ant, next_room);
	}
	else
		ant->has_moved = 1;
}
