/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conflicts.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 02:56:32 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/17 02:56:34 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int	cmp_val_to_path(int room, t_list *path, int *conflict)
{
	t_list *iter;

	iter = path;
	while (iter)
	{
		if (room == *(int *)iter->content)
		{
			*conflict = room;
			return (1);
		}
		iter = iter->next;
	}
	return (0);
}

static	int	cmp_val_to_rem_paths(int room, t_list *remaining_paths, int *conflict)
{
	t_list *iter;

	iter = remaining_paths;
	while (iter)
	{
		if (cmp_val_to_path(room, iter->content, conflict) == 1)
			return (1);
		iter = iter->next;
	}
	return (0);
}

static	int	cmp_path_to_rem_paths(t_list *path, t_list *remaining_paths, int *conflict)
{
	t_list *iter;
	int		room;

	iter = path->next;
	while (iter)
	{
		room = *(int *)iter->content;
		if (cmp_val_to_rem_paths(room , remaining_paths, conflict) == 1)
			return (1);
		iter = iter->next;
	}
	return (0);
}

int			conflicts(t_list *paths, int *conflict, t_pathdata *data)
{
	t_list *iter;
	t_list *remaining_paths;

	iter = paths;
	if (iter->next == NULL)
		return (0);

	remaining_paths = iter->next;
	while (iter->next)
	{
		if (cmp_path_to_rem_paths(iter->content, remaining_paths, conflict) == 1)
		{
			if (*conflict != data->end && *conflict != data->start)
				return (1);
		}
		iter = iter->next;
		if (iter == NULL)
			break;
		remaining_paths = iter->next;
		if (remaining_paths == NULL)
			break ;
	}
	return (0);
}
