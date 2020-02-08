/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   try_superpos.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 08:49:11 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/20 09:14:58 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	try_superpos(t_data *data, t_pathdata *path_data)
{
	while (eval_paths(data, path_data) == 0)
	{
		search_maze(path_data);
		path_data->total_paths = (int)ft_listlen(path_data->paths);
		if (path_data->total_paths >= path_data->path_threshold)
			break ;
	}
	if (path_data->total_paths <= 0)
		error_exec(26, data, path_data);
	return (0);
}
