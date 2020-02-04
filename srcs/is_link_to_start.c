/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_link_to_start.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 16:34:07 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/04 16:34:08 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	is_link_to_start(t_pathdata *data, int room)
{
	int i;
	int links;
	int link;
	int	start_conns;

	start_conns = 0;
	i = 0;
	links = data->links_num[data->start];
	while (i < links)
	{
		link = data->links[data->start][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (link == room)
			return (1);
		i++;
	}
	return (0);
}
