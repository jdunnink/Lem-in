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

void	init_pathdata(t_data **data, t_pathdata **path_data)
{
	t_pathdata *new;

	new = (t_pathdata *)malloc(sizeof(t_pathdata));
	if (!new)
		error_input(4, *data, NULL);
	new->explore_ants = __INT_MAX__;
	new->ants_at_start = new->explore_ants;
	new->ants_in_maze = 0;
	new->ants_at_end = 0;
	new->rooms = (*data)->rooms;
	new->total_links = (*data)->total_links;
	new->start = (*data)->start;
	new->end = (*data)->end;
	new->links = (*data)->links;
	new->links_num = (*data)->links_num;
	new->state = (*data)->state;
	new->pheromone = (*data)->pheromone;
	new->active_ants = NULL;
	new->total_paths = 0;
	if (new->links_num[new->end] < new->links_num[new->start])
		new->path_threshold = new->links_num[new->end];
	else
		new->path_threshold = new->links_num[new->start];
	new->paths = NULL;
	*path_data = new;
}
