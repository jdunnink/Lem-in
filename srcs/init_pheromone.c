/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_pheromone.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 11:36:58 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:45:36 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	init_pheromone(t_data **data)
{
	float	*new;
	int		rooms;
	int		ants;
	int		i;

	ants = (*data)->ants;
	rooms = (*data)->rooms;
	new = (float *)malloc(sizeof(float) * rooms);
	if (!new)
		error_input(4, *data, NULL);
	i = 0;
	while (i < rooms)
	{
		new[i] = 0.000000;
		if (i == (*data)->start)
			new[i] = 1000.000000;
		else if (i == (*data)->end)
			new[i] = -1000.000000;
		i++;
	}
	(*data)->pheromone = new;
}
