/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   block_link.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 17:09:38 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/05 09:15:13 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	block_reverse(t_data *data, int src, int dst)
{
	int i;
	int links_num;

	links_num = data->links_num[src];
	i = 0;
	while (i < links_num)
	{
		if (data->links[src][i] == dst)
		{
			data->links[src][i] = -1;
			return ;
		}
		i++;
	}
}

void			block_link(t_data *data, int room)
{
	int i;
	int links_num;

	links_num = data->links_num[room];
	i = 0;
	while (i < links_num)
	{
		if (data->links[room][i] != -1)
		{
			block_reverse(data, data->links[room][i], room);
			data->links[room][i] = -1;
			return ;
		}
		i++;
	}
}
