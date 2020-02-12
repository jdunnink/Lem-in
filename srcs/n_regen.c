/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_regen.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 15:22:45 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/08 15:22:48 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	n_regen is used to regerate the tail of a path branch, which
**	has been seperated in n_split_cycles. The origin list is parsed
**	until a room is found that is connected to the tail of
**	the branch. From this point the origin list is copied and
**	appended to the branch.
**
**	example:
**	starting branch: 8, 7, 6
**	origin: 4, 3, 2, 1
**	branch occurred at room 2
**
**	ending branch: 8, 7, 6, 2, 1
*/

void	n_regen(t_data *d, t_list *branch, t_list *origin)
{
	t_list *i;
	t_list *b_tail;
	t_list *tail_ptr;

	tail_ptr = NULL;
	b_tail = branch;
	while (branch && b_tail->next)
		b_tail = b_tail->next;
	i = origin;
	while (i)
	{
		if (n_conn(d, *(int *)i->content, *(int *)b_tail->content) == 1 &&
			ft_lstcontains(branch, *(int *)i->content) == 0)
		{
			tail_ptr = i;
			break ;
		}
		i = i->next;
	}
	if (tail_ptr != NULL)
		b_tail->next = ft_lstcpy(tail_ptr);
}
