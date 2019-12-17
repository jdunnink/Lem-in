/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_room.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 17:21:41 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:43:31 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	add_next_name(char *name, t_data **data)
{
	int		len;
	int		i;
	char	**new_array;
	char	**old_array;

	old_array = (*data)->room_names;
	len = ft_strarrlen(old_array);
	new_array = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_array)
		error_input(4, *data, name);
	new_array[len] = NULL;
	i = 0;
	while (i < len - 1)
	{
		new_array[i] = old_array[i];
		old_array[i] = NULL;
		i++;
	}
	new_array[len - 1] = ft_strdup(name);
	ft_freestrarr(old_array);
	(*data)->room_names = new_array;
}

static	void	add_name(char *name, t_data **data)
{
	char **new;

	if ((*data)->room_names == NULL)
	{
		new = (char **)malloc(sizeof(char *) * 2);
		if (!new)
			error_input(4, *data, name);
		new[0] = ft_strdup(name);
		new[1] = NULL;
		(*data)->room_names = new;
	}
	else
		add_next_name(name, data);
}

void			add_room(char *room, t_data **data, int *type)
{
	char	**array;
	int		room_index;

	room_index = (*data)->rooms;
	if ((*type == 1 && (*data)->start != -1) ||
		(*type == -1 && (*data)->end != -1))
		error_input(7, *data, room);
	if (*type == 1)
		(*data)->start = room_index;
	else if (*type == -1)
		(*data)->end = room_index;
	if (*type != 0)
		*type = 0;
	(*data)->rooms = (*data)->rooms + 1;
	array = ft_strsplit(room);
	if (get_room_index(array[0], *data) != -1)
		error_input(3, *data, room);
	add_name(array[0], data);
	ft_freestrarr(array);
}
