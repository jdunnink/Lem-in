/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_room_index.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 21:04:46 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:44:53 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**  return the index of a room by looking up the roomname
**  within the room_names array. returns -1 if the roomname
**  is not recognized.
*/

int	get_room_index(char *roomname, t_data *data)
{
	char	**names;
	int		i;

	names = data->room_names;
	i = 0;
	if (names == NULL)
		return (-1);
	while (names[i] != NULL)
	{
		if (strcmp(names[i], roomname) == 0)
			return (i);
		i++;
	}
	return (-1);
}
