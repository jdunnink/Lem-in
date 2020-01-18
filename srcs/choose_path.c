/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   choose_path.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/18 12:58:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/18 12:58:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	free_tmp_paths(t_pathdata *data)
{
	t_list *iter;
	t_list *curr;

	iter = data->tmp_paths;
	while (iter)
	{
		curr = iter->content;
		ft_lstdel(&curr, &ft_del);
		iter->content = NULL;
		iter = iter->next;
	}
	ft_lstdel(&data->tmp_paths, &ft_del);
	data->tmp_paths = NULL;
}

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

static	t_list *get_shortest(t_list *paths)
{
	int		shortest;
	int		curr_len;
	t_list	*iter;
	t_list  *target;

	shortest = __INT_MAX__;
	iter = paths;
	while (iter)
	{
		curr_len = ft_listlen(iter->content);
		if (curr_len < shortest)
		{
			shortest = curr_len;
			target = iter->content;
		}
		iter = iter->next;
	}
	return (target);
}

/*

static	int check_dup(int num, t_list *rem_path)
{
	t_list *iter;

	iter = rem_path;
	while (iter)
	{
		if (*(int *)iter->content == num)
			return (1);
		iter = iter->next;
	}
	return (0);
}

static	int		has_dup(t_list *path)
{
	t_list *iter;
	int		curr;

	iter = path;
	while (iter->next)
	{
		curr = *(int *)iter->content;
		if (check_dup(curr, iter->next) == 1)
			return (1);
		iter = iter->next;
	}
	return (0);
}

static	t_list *get_longest(t_list *paths)
{
	int		longest;
	int		curr_len;
	t_list	*iter;
	t_list  *target;

	longest = 0;
	iter = paths;
	while (iter)
	{
		curr_len = ft_listlen(iter->content);
		if (curr_len > longest && has_dup(iter->content) == 0)
		{
			longest = curr_len;
			target = iter->content;
		}
		iter = iter->next;
	}
	return (target);
}

*/

void	choose_path(t_pathdata *data)
{
	t_list *target;

	if (data->total_tmp_paths > 0)
	{
//		target = get_longest(data->tmp_paths);
		target = get_shortest(data->tmp_paths);
		target = ft_lstcpy(target);
		mark_path(target, data);
		free_tmp_paths(data);
		data->total_tmp_paths = 0;
		ft_lstappend(&data->paths, target, sizeof(t_list *));
		data->total_paths += 1;
	}

//	show_paths(data->paths);
//	exit (0);
}