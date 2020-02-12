/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_take_origin.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 14:05:41 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/12 14:05:41 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	move_to_last_cycle(int start, t_list **ptr, t_list **path)
{
	t_list *iter;

	iter = *path;
	while (iter)
	{
		if (*(int *)iter->content == start)
			*ptr = iter;
		iter = iter->next;
	}
}

void			n_take_origin(t_list **path)
{
	t_list	*new;
	t_list	*iter;
	int		start;

	start = *(int *)(*path)->content;
	move_to_last_cycle(start, &iter, path);
	new = ft_lstcpy(iter);
	ft_lstdel(path, &ft_del);
	*path = new;
}
