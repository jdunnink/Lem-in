/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 09:03:08 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/10 09:03:08 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		reset_searchmap(t_pathdata *data)
{
	int		*state;
	float	*pheromone;
	int		i;

	i = 0;
	data->ants_at_end = 0;
	data->ants_in_maze = 0;
	data->ants_at_start = data->explore_ants;
	pheromone = data->pheromone;
	state = data->state;
	while (i < data->rooms)
	{
		if (pheromone[i] < 10000 && i != data->end)
			pheromone[i] = 0;
		state[i] = 0;
		i++;
	}
	state[data->start] = data->ants_at_start;
	pheromone[data->start] = state[data->start] * 0.000001;
}

#include <stdio.h>

static	void	mark_path(t_list *path, t_pathdata *data)
{
	t_list	*iter;
	int		room_index;
	float	trail;

	trail = 15000;
	iter = path;
	while (iter)
	{
		room_index = *(int *)iter->content;
		if (room_index == data->end)
			data->pheromone[room_index] = trail * -1;
		else
		{
			if (data->pheromone[room_index] < 15000)
				data->pheromone[room_index] = trail;
			trail = trail * 1.00001;
		}
		iter = iter->next;
	}
}

static	void	add_path(t_list **new_path, t_pathdata *data)
{
	ft_lstappend(&(data->paths), *new_path, sizeof(t_list *));
	data->total_paths += 1;
}

static	void	del_active_ants(t_list **active_ants)
{
	t_list		*iter;
	t_exp_ant	*ant;

	iter = *active_ants;
	while (iter)
	{
		ant = iter->content;
		if (ant->path != NULL)
		{
			ft_lstdel(&ant->path, &ft_del);
			ant->path = NULL;
		}
		free(ant);
		iter->content = NULL;
		iter = iter->next;
	}
	ft_lstdel(active_ants, &ft_del);
	*active_ants = NULL;
}

#include <stdio.h>

void			process_path(t_pathdata *data)
{
	t_list		*iter;
	t_exp_ant	*ant;

	iter = data->active_ants;
	while (iter)
	{
		ant = iter->content;
		if (ant->room == data->end)
		{
//			printf("	a new path of %lu length has been found! clearing maze\n", ft_listlen(ant->path));
			mark_path(ant->path, data);
			add_path(&ant->path, data);
//			show_paths(data->paths);
			ant->path = NULL;
			del_active_ants(&data->active_ants);
			reset_searchmap(data);
			create_phero_trail(data);
			return ;
		}
		else
			iter = iter->next;
	}
}
