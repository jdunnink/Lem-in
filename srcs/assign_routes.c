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

static	void	assign_to_ant(t_list *paths, t_ant *ant, int *counter)
{
	int i;
	int curr_score;
	int best_score;
	int	path_cnt;
	t_list *best_path;

	i = 0;
	curr_score = 0;
	best_score = __INT_MAX__;
	best_path = NULL;
	while (paths)
	{
		curr_score = (int)ft_listlen(paths->content) + counter[i];
		if (curr_score < best_score)
		{
			best_score = curr_score;
			best_path = paths->content;
			path_cnt = i;
		}
		paths = paths->next;
		i++;
	}
	counter[path_cnt]++;
	ant->target_path = ft_lstcpy(best_path);
}

void			assign_routes(t_data *data, t_pathdata *path_data)
{
	t_list	*iter;
	t_ant	*curr_ant;
	int		*counter;

	counter = ft_intnew(path_data->total_paths);
	iter = data->active_ants;
	while (iter)
	{
		curr_ant = iter->content;
		assign_to_ant(path_data->paths, curr_ant, counter);
		iter = iter->next;
	}
	free(counter);
	free_paths(path_data);
}
