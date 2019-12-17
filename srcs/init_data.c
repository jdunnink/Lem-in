/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 14:36:38 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:53:34 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	init_data(t_data **data)
{
	*data = NULL;
	*data = (t_data *)malloc(sizeof(t_data));
	if (!(*data))
		error_input(4, *data, NULL);
	(*data)->ants = 0;
	(*data)->ants_at_start = 0;
	(*data)->ants_in_maze = 0;
	(*data)->ants_at_end = 0;
	(*data)->rooms = 0;
	(*data)->total_links = 0;
	(*data)->start = -1;
	(*data)->end = -1;
	(*data)->room_names = NULL;
	(*data)->links = NULL;
	(*data)->links_num = NULL;
	(*data)->state = NULL;
	(*data)->pheromone = NULL;
	(*data)->move_list = NULL;
	(*data)->active_ants = NULL;
	(*data)->lines = NULL;
}
