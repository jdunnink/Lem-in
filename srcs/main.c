/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 08:49:11 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/08 10:44:37 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	setup(t_data **data, t_pathdata **path_data)
{
	read_input(data);
	verify_data(*data);
	init_state(data);
	init_pheromone(data);
	(*data)->ants_at_start = (*data)->ants;
	init_pathdata(data, path_data);
}

static	void	dump_lines(t_data *data)
{
	t_list	*iter;
	char	*curr;

	iter = data->lines;
	while (iter)
	{
		curr = iter->content;
		ft_putendl(curr);
		iter = iter->next;
	}
	ft_lstdel(&data->lines, &ft_del);
	ft_putchar('\n');
	data->lines = NULL;
}

#include <stdio.h>

int				main(void)
{
	t_data		*data;
	t_pathdata	*path_data;
	int			i;
	int			cmp;

	setup(&data, &path_data);

//	printf("	searching maze..");

	path_data->path_threshold = 1;

	i = 0;
	while (path_data->total_paths < path_data->orig_threshold)
	{
		cmp = path_data->orig_threshold - path_data->total_paths;
		search_maze(path_data);
		if (path_data->orig_threshold - path_data->total_paths <= cmp)
			i++;
		if (i > path_data->orig_threshold * 4 && path_data->total_paths < path_data->orig_threshold)
		{
			reset_map(data);
			search_maze(path_data);
			i = 0;
			path_data->orig_threshold--;
		}
	}


//	show_paths(path_data->paths);
//	exit (0);

	reset_map(data);
	dump_lines(data);

//	printf("	traversing maze..");

	traverse_maze(data, path_data);

	free(path_data);
	free_data(&data);
	return (0);
}
