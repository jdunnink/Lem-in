/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_conn.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 15:21:44 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/08 15:21:45 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	n_conn checks if two rooms are connected.
*/

int		n_conn(t_data *d, int room_1, int room_2)
{
	int i;
	int links;
	int link;

	i = 0;
	links = d->links_num[room_1];
	while (i < links)
	{
		link = d->links[room_1][i];
		if (link != -1 && link == room_2)
			return (1);
		i++;
	}
	return (0);
}
