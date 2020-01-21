/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_link_storage.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 08:57:05 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/08 08:57:05 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	init_links_lookup(t_data **data)
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

static	void	init_active_links_num(t_data **data)
{
	int rooms;
	int i;

	rooms = (*data)->rooms;
	(*data)->active_links_num = (int *)malloc(sizeof(int) * rooms);
	if (!(*data)->active_links_num)
		error_input(4, *data, NULL);
	i = 0;
	while (i < rooms)
	{
		(*data)->active_links_num[i] = (*data)->links_num[i];
		i++;
	}
}

void			init_link_storage(t_data **data)
{
	if ((*data)->links == NULL)
		init_links_lookup(data);
	if ((*data)->links_num == NULL)
		init_links_num(data);
	if ((*data)->active_links_num == NULL && (*data)->links_num != NULL)
		init_active_links_num(data);
}
