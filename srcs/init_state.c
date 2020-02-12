/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_state.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 22:18:26 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:45:49 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	init_state initialized the state element used for maze traversal
**	if a rooms state is 0, it is empty, otherwise it is not.
**
**	examples:
**
**	room 56 is empty
**	---------------->		data->state[56] = 0;
**	room 77 is not empty
**	---------------->		data->state[77] = 1;
*/

void	init_state(t_data **data)
{
	int	i;
	int	rooms;
	int	*state;

	rooms = (*data)->rooms;
	if (rooms == 0)
		return ;
	state = (int *)malloc(sizeof(int *) * rooms);
	if (!state)
		error_input(4, *data, NULL);
	i = 0;
	while (i < rooms)
	{
		if (i == (*data)->start)
			state[i] = __INT_MAX__;
		else
			state[i] = 0;
		i++;
	}
	(*data)->state = state;
}
