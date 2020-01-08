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

int				main(void)
{
	t_data		*data;
	t_pathdata	*path_data;

	setup(&data, &path_data);
	search_maze(path_data);
	reset_map(data);
	dump_lines(data);
	traverse_maze(data, path_data);
	free(path_data);
	free_data(&data);
	return (0);
}
