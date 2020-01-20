/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_explorer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 08:51:37 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/10 08:51:38 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int		check_deadends(t_pathdata *data, t_exp_ant *ant, int best)
{
	if (best == -1)
	{
		ant->has_moved = 1;
		return (1);
	}
	if (data->links_num[ant->room] == 1)
	{
		if (ant->room != data->end && ant->room != data->start)
		{
			ant->has_moved = 1;
			return (1);
		}
	}
	return (0);
}

static	void	exp_move_to_room(t_pathdata *data, t_exp_ant *ant, int best)
{
	int next_room;

	if (check_deadends(data, ant, best) == 1)
		return ;
	next_room = data->links[ant->room][best];
	if (ant->room == data->start && ant->number == 0)
	{
		(data->ants_at_start)--;
		(data->ants_in_maze)++;
		ant->number = (data->explore_ants - data->ants_at_start);
	}
	if (next_room == data->end)
	{
		(data->ants_in_maze)--;
		(data->ants_at_end)++;
	}
	ft_lstpushfront(&next_room, &ant->path, sizeof(int *));
	data->state[ant->room]--;
	data->state[next_room]++;
	if (data->links_num[next_room] == 1 &&
		next_room != data->end && next_room != data->start)
		data->pheromone[next_room] = 12000;
	ant->has_moved = 1;
	ant->room = next_room;
}

static	int		check_end(t_pathdata *data, int link, int *best_link, int i)
{
	if (link == data->end)
	{
		*best_link = i;
		return (1);
	}
	return (0);
}

void			move_explorer(t_pathdata *data, t_exp_ant *ant)
{
	t_varpack1 v;

	v.i = 0;
	v.best_link = -1;
	v.best_rating = 999999;
	while (v.i < data->links_num[ant->room])
	{
		v.link = data->links[ant->room][v.i];
		if (check_end(data, v.link, &v.best_link, v.i) == 1)
			break ;
		else if (data->state[v.link] == 0)
		{
			v.link_rating = data->pheromone[v.link];
			v.link = v.i;
			if (v.link_rating < v.best_rating)
			{
				v.best_rating = v.link_rating;
				v.best_link = v.i;
			}
		}
		v.i++;
	}
	exp_move_to_room(data, ant, v.best_link);
}
