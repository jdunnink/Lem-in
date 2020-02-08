/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_open_links.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:32:11 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/05 15:32:12 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		n_open_links(t_data *data, int *state, int room, int src)
{
	int i;
	int links;
	int link;
	int open;

	i = 0;
	open = 0;
	links = data->links_num[room];
	while (i < links)
	{
		link = data->links[room][i];
		if (link == -1)
		{
			i++;
			continue ;
		}
		if (state[link] == 0 && link != src)
			open++;
		i++;
	}
	return (open);
}