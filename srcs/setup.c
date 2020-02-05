/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 14:17:36 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/05 14:17:37 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	setup(t_data **data, t_pathdata **path_data)
{
	read_input(data);
	verify_data(*data);
	init_state(data);
	(*data)->ants_at_start = (*data)->ants;
	filter_deadends(data);
	init_pathdata(data, path_data);
}
