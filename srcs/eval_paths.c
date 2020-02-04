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

#include <stdio.h>

static	void	distribute(t_pathdata *data, int *counter)
{
	int i;
	int curr_score;
	int best_score;
	int	path_cnt;
	t_list *iter;
	t_list *path;
	t_list *best_path;

	i = 0;
	curr_score = 0;
	best_score = __INT_MAX__;
	best_path = NULL;
	iter = data->paths;
	while (iter)
	{
		path = iter->content;
		curr_score =  (int)ft_listlen(path) + counter[i];
		if (curr_score < best_score)
		{
			best_score = curr_score;
			best_path = path;
			path_cnt = i;
		}
		iter = iter->next;
		i++;
	}
//	printf("	assigning route: \n");
//	print_path(best_path);
	counter[path_cnt]++;
}

static  int get_first_room(t_list *path)
{
    t_list *iter;

    iter = path;
    while (iter->next)
        iter = iter->next;
    return (*(int *)iter->content);
}

static	void	show_pathlens(t_list *paths)
{
	t_list *iter;
	size_t len;
	int i;

	i = 0;
	iter = paths;
	while (iter)
	{
		len = ft_listlen(iter->content);
//		printf("	path %i starting with room %i has len %lu\n", i, get_first_room(iter->content), len);
		iter = iter->next;
		i++;
	}
}

static	int	array_contains(int *array, int len, int value)
{
	int i;
	int zeros;
	i = 0;

	zeros = 0;
	while (i < len)
	{
		if (array[i] == 0)
			zeros++;
		i++;
	}
	if (zeros > 3)
		return (1);
	return (0);
}

int		eval_paths(t_data *data, t_pathdata *path_data)
{
	int		*counter;
	int		i;

	show_pathlens(path_data->paths);

	if (path_data->total_paths == 0)
		return (0);

	counter = ft_intnew(path_data->total_paths);
//	printf("	%i different paths\n", path_data->total_paths);
    i = 0;
	while (i < data->ants)
    {
		distribute(path_data, counter);
        i++;
    }
//	ft_putnbr_array("path distribution", counter, path_data->total_paths);
	free(counter);
	if (array_contains(counter, path_data->total_paths, 0) == 1)
	{
//		printf("	current solution would contain unused paths\n");
//		printf("	blocking last finished path\n");
//		printf("	rerunning BFS\n");
		free_paths(path_data);
		reset_bfs_data(data, path_data);
		return (0);
	}
	else
		return (1);
}