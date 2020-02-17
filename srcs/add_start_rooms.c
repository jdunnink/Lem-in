/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_start_rooms.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 09:11:33 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/17 09:11:34 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	add_start_rooms(int start, t_list *paths)
{
	t_list	*iter;
	int		room;

	iter = paths;
	while (iter)
	{
		room = start;
		ft_lstpushback((t_list **)&iter->content, &room, sizeof(int *));
		iter = iter->next;
	}
}
