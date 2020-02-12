/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_move_list.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/09 13:37:57 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/09 13:37:58 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	print_move_list prints the moves
**	currently stored in the move_list element.
*/

void	print_move_list(t_data *data)
{
	t_list	*iter;
	char	*move;

	if (data->move_list == NULL)
		return ;
	iter = data->move_list;
	while (iter)
	{
		move = iter->content;
		ft_putstr(move);
		if (iter->next != NULL)
			ft_putchar(' ');
		iter = iter->next;
	}
	ft_putchar('\n');
}
