/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_maze.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 08:30:10 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/08 17:02:12 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			search_maze(t_pathdata *data)
{
	int			curr_depth;

	curr_depth = 1;
	while (curr_depth < 100)
	{
		process_rooms(data, &curr_depth);
		push_finished(data);
		if (active_end_conn(data) == data->path_threshold)
		{
			if ((int)ft_listlen(data->finish_order) >= data->path_threshold)
				break ;
		}
	}
	parse_paths(data);
}
