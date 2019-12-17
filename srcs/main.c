/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 08:49:11 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:46:14 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	//	REMOVE STDIO INCLUDE FROM LIBFT (FT_PUTFLOAT USES CLIB PRINTF)
*/

static	void	cleanup(t_data *data, t_pathdata *path_data)
{
	int i;

	free(path_data);
	path_data = NULL;
	ft_freestrarr(data->room_names);
	data->room_names = NULL;
	i = 0;
	while (i < data->rooms)
	{
		free(data->links[i]);
		i++;
	}
	free(data->links);
	data->links = NULL;
	free(data->state);
	data->state = NULL;
	free(data->pheromone);
	data->pheromone = NULL;
	free(data->links_num);
	data->links_num = NULL;
	free(data);
	data = NULL;
}

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
		write(1, curr, iter->content_size);
		write(1, "\n", 1);
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
	cleanup(data, path_data);
	return (0);
}
