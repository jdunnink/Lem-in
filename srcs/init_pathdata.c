/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_pathdata.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 07:37:04 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/10 07:37:04 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int	init_bfs_data(t_pathdata **new)
{
	t_pathdata	*curr;
	int			i;

	curr = *new;
	curr->bfs_data = (int **)malloc(sizeof(int *) * curr->rooms);
	if (!curr->bfs_data)
		return (0);
	i = 0;
	while (i < curr->rooms)
	{
		curr->bfs_data[i] = (int *)malloc(sizeof(int) * 3);
		if (!curr->bfs_data[i])
			return (0);
		curr->bfs_data[i][0] = 0;
		curr->bfs_data[i][1] = 0;
		curr->bfs_data[i][2] = 0;
		i++;
	}
	curr->diff_override = NULL;
	curr->same_override = NULL;
	curr->finish_order = NULL;
	return (1);
}

void	init_pathdata(t_data **data, t_pathdata **path_data)
{
	t_pathdata *new;

	new = (t_pathdata *)malloc(sizeof(t_pathdata));
	if (!new)
		error_input(4, *data, NULL);
	new->rooms = (*data)->rooms;
	new->total_links = (*data)->total_links;
	new->start = (*data)->start;
	new->end = (*data)->end;
	new->links = (*data)->links;
	new->links_num = (*data)->links_num;
	new->active_links_num = (*data)->active_links_num;
	new->total_paths = 0;
	if (new->links_num[new->end] < new->links_num[new->start])
		new->path_threshold = new->links_num[new->end];
	else
		new->path_threshold = new->links_num[new->start];
	new->paths = NULL;
	if (init_bfs_data(&new) == 0)
		error_input(4, *data, NULL);
	*path_data = new;
}
