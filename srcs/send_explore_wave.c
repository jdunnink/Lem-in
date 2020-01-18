/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   send_explore_wave.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 02:49:29 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/17 02:49:31 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	spawn_explorer(t_pathdata *data)
{
	t_exp_ant *new_exp;

	if (data->ants_at_start == 0)
		return ;
	new_exp = (t_exp_ant *)malloc(sizeof(t_exp_ant));
	if (!new_exp)
		error_exec(2, NULL, data);
	new_exp->room = data->start;
	new_exp->has_moved = 0;
	new_exp->number = 0;
	new_exp->path = NULL;
	ft_lstappend(&(data->active_ants), new_exp, sizeof(t_exp_ant));
}

static void		move_explorers(t_pathdata *data)
{
	t_list		*iter;
	t_exp_ant	*curr;
	int			last_end_count;

	iter = data->active_ants;
	last_end_count = data->state[data->end];
	while (iter)
	{
		curr = iter->content;
		if (curr->has_moved == 0)
			move_explorer(data, curr);
		iter = iter->next;
	}
	if (data->state[data->end] != last_end_count)
		process_path(data);
}

#include <stdio.h>

/*

static	void	show_phero(float *array, int rooms)
{
	int i;

	i = 0;
	while (i < rooms)
	{
		printf("	[%i] => %0.6f\n", i, array[i]);
		i++;
	}
}

*/

static	int	pop_conflict(t_list **conflicts)
{
	t_list *iter;
	int		conflict_index;

	conflict_index = 0;
	iter = *conflicts;
	conflict_index = *(int *)iter->content;
	ft_lstdelfront(conflicts);
	return (conflict_index);
}



int				send_explore_wave(t_pathdata *data)
{
	int links_num;

//	printf("	send explore wave is called!\n");
//	show_phero(data->pheromone, data->rooms);

	if (moves(data->active_ants) > 0)
		move_explorers(data);
	links_num = open_links(data, data->start);
//	printf("	%i open links detected!\n", links_num);
	if (links_num > data->ants_at_start)
		links_num = data->ants_at_start;
	else if (links_num == 0 && data->total_paths == 0 && ft_listlen(data->conflicts) > 0)
	{
		data->pheromone[pop_conflict(&data->conflicts)] = 0;
//		printf("	the only possible path is blocked! --> opening blocked room\n");
		data->orig_threshold--;
		return (1);
	}
	while (links_num > 0)
	{
		spawn_explorer(data);
		links_num--;
	}
	if (moves(data->active_ants) > 0)
		move_explorers(data);
	return (1);
}
