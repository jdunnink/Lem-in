/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_move_output.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 09:14:41 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/17 09:14:42 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	save_move_output(int ant_nbr, int next_room, t_data *data)
{
	char	*move_output;
	char	*ant_number;
	char	*room_name;

	ant_number = ft_itoa(ant_nbr);
	room_name = get_room_name(next_room, data);
	move_output = ft_strjoin_free("L", ant_number, 2);
	move_output = ft_strjoin_free(move_output, "-", 1);
	move_output = ft_strjoin_free(move_output, room_name, 1);
	ft_lstappend(&(data->move_list), move_output, sizeof(char *));
}
