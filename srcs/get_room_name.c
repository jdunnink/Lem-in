/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_room_name.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 21:04:09 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:45:03 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	get_room_name returns the name of a room as a string.
**	requires the index of the room.
*/

char	*get_room_name(int room_index, t_data *data)
{
	return (data->room_names[room_index]);
}
