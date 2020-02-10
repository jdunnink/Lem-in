/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_pathdata.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 14:37:13 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/10 14:37:14 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	free_bfs_data(int rooms, int **array)
{
	int i;

	i = 0;
	while (i < rooms)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void			free_pathdata(t_pathdata *target)
{
	if (target->bfs_data != NULL)
		free_bfs_data(target->rooms, target->bfs_data);
	if (target->finish_order != NULL)
		ft_lstdel(&target->finish_order, &ft_del);
	if (target->diff_override != NULL)
		ft_lstdel(&target->diff_override, &ft_del);
	if (target->paths != NULL)
		free_paths(target);
	free(target);
}
