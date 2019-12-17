/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assign_routes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 02:07:09 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/17 02:07:11 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		assign_to_ant(t_ant *ant, t_pathdata *path_data, int *counter)
{
	int path_i;
	int	score;
	int lowest_score;
	int best_path;

	score = 0;
	lowest_score = ft_listlen(get_path(path_data, 0)) + counter[0];
	path_i = 1;
	best_path = path_i - 1;
	while (path_i < path_data->total_paths)
	{
		score = ft_listlen(get_path(path_data, path_i)) + counter[path_i];
		if (score < lowest_score)
		{
			best_path = path_i;
			lowest_score = score;
		}
		path_i++;
	}
	ant->target_path = get_pathcpy(path_data, best_path);
	counter[best_path]++;
}

void			assign_routes(t_data *data, t_pathdata *path_data)
{
	t_list	*iter;
	t_ant	*curr_ant;
	int		*counter;
	int		i;

	counter = ft_intnew(path_data->total_paths);
	iter = data->active_ants;
	i = 0;
	while (iter)
	{
		curr_ant = iter->content;
		assign_to_ant(curr_ant, path_data, counter);
		i++;
		iter = iter->next;
	}
	free(counter);
	free_paths(path_data);
}
