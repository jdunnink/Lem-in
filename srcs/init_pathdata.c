/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_pathdata.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 07:37:04 by jdunnink       #+#    #+#                */
/*   Updated: 2020/02/16 05:07:14 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	init_pathdata initialized the main pathdata struct by
**	extending from the main data struct.
*/

void		init_pathdata(t_data **data, t_pathdata **path_data)
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
	new->total_paths = 0;
	new->paths = NULL;
	*path_data = new;
}
