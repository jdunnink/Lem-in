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

static	void	setup(t_data **data, t_pathdata **path_data)
{
	read_input(data);
	verify_data(*data);
	init_state(data);
	(*data)->ants_at_start = (*data)->ants;
	filter_deadends(data);
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

	setup(&data, &path_data);


	search_maze(path_data);

	printf("	%i total_paths found!\n", path_data->total_paths);
	show_paths(path_data->paths);

	dump_lines(data);
	traverse_maze(data, path_data);
	free(path_data);
	free_data(&data);
	return (0);
}
