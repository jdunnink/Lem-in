/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_conflicts.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 02:56:32 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/17 02:56:34 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	cmp_val_to_path(int room, t_list *path, int *conflict)
{
	t_list *iter;

	iter = path;
	while (iter)
	{
		if (room == *(int *)iter->content)
			(*conflict)++;
		iter = iter->next;
	}
}

static	void	cmp_val_to_rem_paths(int room, t_list *remaining_paths, int *conflict)
{
	t_list *iter;

	iter = remaining_paths;
	while (iter)
	{
		cmp_val_to_path(room, iter->content, conflict);
		iter = iter->next;
	}
}

static	void	cmp_path_to_rem_paths(t_list *path, t_list *remaining_paths, int *conflict)
{
	t_list *iter;
	int		room;

	iter = path->next;
	while (iter)
	{
		room = *(int *)iter->content;
		cmp_val_to_rem_paths(room , remaining_paths, conflict);
		iter = iter->next;
	}
}

int			count_conflicts(t_list *paths)
{
	t_list *iter;
	t_list *remaining_paths;
	int conflicts;

	if (!paths)
		return (0);

	iter = paths;
	if (iter->next == NULL)
		return (0);
	conflicts = 0;
	remaining_paths = iter->next;
	while (iter->next)
	{
		cmp_path_to_rem_paths(iter->content, remaining_paths, &conflicts);
		iter = iter->next;
		if (iter == NULL)
			break;
		remaining_paths = iter->next;
		if (remaining_paths == NULL)
			break ;
	}
	return (conflicts);
}