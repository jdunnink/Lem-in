/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 08:49:11 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/20 09:14:58 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				main(void)
{
	t_data		*data;
	t_pathdata	*path_data;

	setup(&data, &path_data);
	if (try_normal(data) == 0)
		try_superpos(data, path_data);
	dump_lines(data);
	traverse_maze(data, path_data);
	free(path_data);
	free_data(&data);
	return (0);
}
