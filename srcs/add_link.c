/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_link.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 20:20:40 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:42:55 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	init_links(t_data **data)
{
	int	rooms;
	int	**array;
	int	i;

	rooms = (*data)->rooms;
	if (rooms <= 0)
		error_input(6, *data, NULL);
	array = (int **)malloc(sizeof(int *) * rooms);
	if (!array)
		error_input(4, *data, NULL);
	i = 0;
	while (i < rooms)
	{
		array[i] = (int *)malloc(sizeof(int) * 1);
		if (!(array[i]))
		{
			free_2d_int_array(i - 1, array);
			error_input(4, *data, NULL);
		}
		array[i][0] = -1;
		i++;
	}
	(*data)->links = array;
}

static	void	init_links_num(t_data **data)
{
	int rooms;
	int i;

	rooms = (*data)->rooms;
	(*data)->links_num = (int *)malloc(sizeof(int) * rooms);
	if (!(*data)->links_num)
		error_input(4, *data, NULL);
	i = 0;
	while (i < rooms)
	{
		(*data)->links_num[i] = 0;
		i++;
	}
}

static	int		load_old_links(t_data *data, int **array, int src, int dst)
{
	int curr_links;
	int *ptr;
	int i;

	ptr = *array;
	curr_links = ((data->links_num)[src]);
	i = 0;
	while (i < curr_links)
	{
		ptr[i] = data->links[src][i];
		if (ptr[i] == dst)
		{
			free(ptr);
			return (0);
		}
		i++;
	}
	ptr[i] = dst;
	return (1);
}

static	void	process_link(int src_index, int dst_index, t_data **data)
{
	int curr_links;
	int *new_array;

	if (src_index == dst_index)
		return ;
	curr_links = (((*data)->links_num)[src_index]);
	if (curr_links == 0)
		(*data)->links[src_index][0] = dst_index;
	else
	{
		new_array = (int *)malloc(sizeof(int) * (curr_links + 1));
		if (!new_array)
			error_input(4, *data, NULL);
		if (load_old_links(*data, &new_array, src_index, dst_index) == 0)
			return ;
		free((*data)->links[src_index]);
		(*data)->links[src_index] = new_array;
	}
	(((*data)->links_num)[src_index])++;
}

void			add_link(char *link, t_data **data)
{
	char	*src_room;
	char	*dst_room;
	int		src_index;
	int		dst_index;

	if ((*data)->links == NULL)
		init_links(data);
	if ((*data)->links_num == NULL)
		init_links_num(data);
	src_room = ft_strdup_until(link, '-');
	while (*link != '-')
		link++;
	dst_room = ft_strdup(link + 1);
	if (dst_room == NULL)
		error_input(4, *data, link);
	dst_index = get_room_index(dst_room, *data);
	src_index = get_room_index(src_room, *data);
	free(src_room);
	free(dst_room);
	if (dst_index == -1 || src_index == -1)
		return ;
	process_link(src_index, dst_index, data);
	process_link(dst_index, src_index, data);
	(*data)->total_links = (*data)->total_links + 1;
}
