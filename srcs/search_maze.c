/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_maze.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 08:30:10 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/08 17:02:12 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

/*

static	float	get_average_pathlen(t_list *paths)
{
	float		aggregate;
	int			len;
	t_list		*iter;

	aggregate = 0;
	iter = paths;
	while (iter)
	{
		len = ft_listlen(iter->content);
		aggregate += (float)len;
		iter = iter->next;
	}
	return (aggregate / ft_listlen(paths));
}




static	void	show_phero(float *array, int rooms)
{
	int i;

	i = 0;
	while (i < rooms)
	{
		printf("	[%i] => %0.6f\n", i, array[i]);
		i++;
	}
	ft_putchar('\n');
}



static	int		eval_start_conn_phero(t_pathdata *data)
{
	int links;
	int i;
	int link_to_start;

	i = 0;
	links = data->links_num[data->start];
	while (i < links)
	{
		link_to_start = data->links[data->start][i];
		i++;
		if (data->pheromone[link_to_start] < 0)
			return (0);
	}
	return (1);
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

static	void	cleanup_phero(t_pathdata *data)
{
	int i;

	i = 0;
	while (i < data->rooms)
	{
		if (i != data->end && i != data->start)
		{
			if (data->pheromone[i] < 14999)
				data->pheromone[i] = 0;
		}
		i++;
	}
}

void			search_maze(t_pathdata *data)
{
	int		conflict;

//	printf("	search maze is called with %i paths, looking for %i total paths \n", data->total_paths, data->path_threshold);
	cleanup_phero(data);
//	show_phero(data->pheromone, data->rooms);



	create_phero_trail(data);
	while (data->total_paths < data->path_threshold)
	{
		if (send_explore_wave(data) == 0)
			break ;
		spread_pheromones(data);
		recharge_ants(data->active_ants);
	}
	if (data->active_ants != NULL)
		ft_lstdel(&data->active_ants, &del_ant);

//	printf("	%i paths collected while target was %i\n", data->total_paths, data->path_threshold);
//	show_paths(data->paths);


	conflict = -1;

	if (conflicts(data->paths, &conflict) != 0)
	{
//		printf("	%i new conflicts have emerged! --> removing conflicting paths\n", count_conflicts(data->paths));
		conflict = worst_conflict(data);
		ft_lstpushfront(&conflict, &data->conflicts, sizeof(int *));
		data->pheromone[conflict] = 18000;
		del_all_conflicting(data, conflict);
		(data->path_threshold)--;
		search_maze(data);
	}

	if (ft_listlen(data->conflicts) > 0)
	{
		conflict = pop_conflict(&data->conflicts);
		data->pheromone[conflict] = 0;
//		printf("	opening room %i for path traversal\n", conflict);
		data->path_threshold = data->total_paths + 1;
		search_maze(data);
	}

//	printf("	collected (measured: %i/actual: %i) paths with an average length of %0.2f with %i conflicts remaining\n", data->total_paths, (int)ft_listlen(data->paths), get_average_pathlen(data->paths), count_conflicts(data->paths));
}
