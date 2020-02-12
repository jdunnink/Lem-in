/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_movelinks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 15:24:54 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/10 15:24:55 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	n_disable(t_list *path, t_list *macro)
{
	t_list *iter;

	iter = macro;
	while (iter)
	{
		if (iter->content == path)
			iter->content = NULL;
		iter = iter->next;
	}
}

/*
**	n_movelinkes takes a path_batch and
**	sets all the same pointers in the macro list
**	to NULL to prevent double frees when the macro
**	list is removed.
*/

void			n_movelinks(t_list *ret, t_list *macro)
{
	t_list *iter;

	iter = ret;
	while (iter)
	{
		n_disable(iter->content, macro);
		iter = iter->next;
	}
}
