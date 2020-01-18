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

void			search_maze(t_pathdata *data)
{
	int		conflict;
	int		i;
	
//	printf("\n\n	search maze is called with %i paths, looking for %i total paths \n", data->total_paths, data->path_threshold);

//	show_phero(data->pheromone, data->rooms);

	create_phero_trail(data);
	i = 0;
//	printf("	created phero trail --> searching maze\n");
	while ((data->ants_in_maze > 0 || data->ants_at_start > 0) && data->total_tmp_paths < 1)
	{
//		if (eval_start_conn_phero(data) == 1)
//			break ;
//		printf("	%i ants in the maze with %i remaining at start\n %i paths collected", data->ants_in_maze, data->ants_at_start, data->total_tmp_paths);
		if (send_explore_wave(data) == 0)
			break ;
		spread_pheromones(data);
		recharge_ants(data->active_ants);
		i++;
		if (i == 500)
			break ;
	}
//	printf("	searching done --> clearing maze\n");
	clear_maze(data);
	choose_path(data);
//	printf("	%i paths collected while target was %i\n", data->total_paths, data->path_threshold);
	if (data->total_paths == data->path_threshold - 1 && ft_listlen(data->conflicts) == 0)
	{
		data->orig_threshold--;
		return ;
	}
//	show_paths(data->paths);
//	exit (0);


	conflict = -1;

	if (conflicts(data->paths, &conflict, data) != 0)
	{
//		printf("	%i new conflicts have emerged! --> removing conflicting paths\n", count_conflicts(data->paths));
		conflict = worst_conflict(data);
//		printf("	blocking access to room %i\n", conflict);
		ft_lstpushfront(&conflict, &data->conflicts, sizeof(int *));
		data->pheromone[conflict] = 18000;
		del_all_conflicting(data, conflict);
		(data->path_threshold)--;
		return ;
	}

	if (ft_listlen(data->conflicts) > 0)
	{
		conflict = pop_conflict(&data->conflicts);
		data->pheromone[conflict] = 0;
//		printf("	opening room %i for path traversal\n", conflict);
		data->path_threshold = data->total_paths + 1;
		return ;
	}

	if (data->path_threshold < data->orig_threshold)
	{
//		printf("	target threshold of %i has not yet been reached --> finding augmenting paths\n", data->orig_threshold);
		data->path_threshold = data->total_paths + 1;
		return ;
	}

//	printf("	collected (measured: %i/actual: %i) paths with %i conflicts remaining\n", data->total_paths , (int)ft_listlen(data->paths), count_conflicts(data->paths));
}
