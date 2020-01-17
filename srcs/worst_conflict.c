/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   worst_conflict.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 12:49:19 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/17 12:49:20 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

//	return the room that conflicts with the most paths.

static	void	init_hash(int **conflict_hash, int rooms)
{
	int i;

	*conflict_hash = (int *)malloc(sizeof(int) * rooms);
	if(!conflict_hash)
		return ;
	i = 0;
	while (i < rooms)
	{
		(*conflict_hash)[i] = 0;
		i++;
	}
}

static	void	count_rooms(t_list *path, int *conflict_hash, int *last_conflict, int end)
{
	t_list *iter;
	int		room;

	iter = path;
	while (iter)
	{
		room = *(int *)iter->content;
		conflict_hash[room] += 1;
		if (room != end && conflict_hash[room] > 1)
		{
			if (*last_conflict == -1)
				*last_conflict = room;
			else if (conflict_hash[room] >= conflict_hash[*last_conflict])
				*last_conflict = room;
		}
			
		iter = iter->next;
	}
}

static	void	hash_paths(t_list *paths, int *conflict_hash, int *last_conflict, int end)
{
	t_list *iter;

	iter = paths;
	while (iter)
	{
		count_rooms(iter->content, conflict_hash, last_conflict, end);
		iter = iter->next;
	}
}

#include <stdio.h>


/*

static	void	show_hash(int *conflict_hash, int rooms)
{
	int i;

	i = 0;
	while (i < rooms)
	{
		if (conflict_hash[i] > 1)
			printf("	room %i was found %i times\n", i, conflict_hash[i]);
		i++;
	}
}

*/


int	worst_conflict(t_pathdata *data)
{
	int *conflict_hash;
	int	last_conflict;

	last_conflict = -1;
	init_hash(&conflict_hash, data->rooms);
	hash_paths(data->paths, conflict_hash, &last_conflict, data->end);
//	printf("	worst conflict found was %i which occurred %i times\n", last_conflict, conflict_hash[last_conflict]);

//	show_hash(conflict_hash, data->rooms);
	free(conflict_hash);
	return (last_conflict);
}