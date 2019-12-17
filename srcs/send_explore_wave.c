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

int				send_explore_wave(t_pathdata *data)
{
	int links_num;

	if (moves(data->active_ants) > 0)
		move_explorers(data);
	links_num = open_links(data, data->start);
	if (links_num > data->ants_at_start)
		links_num = data->ants_at_start;
	if (links_num == 0 && data->total_paths != 0)
		return (0);
	else if (links_num == 0 && data->total_paths == 0)
		error_exec(3, NULL, data);
	while (links_num > 0)
	{
		spawn_explorer(data);
		links_num--;
	}
	if (moves(data->active_ants) > 0)
		move_explorers(data);
	return (1);
}
