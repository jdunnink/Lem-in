/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_free_paths.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 15:23:34 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/10 15:23:35 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	n_free_paths(t_list *paths)
{
	t_list *iter;
	t_list *curr;

	iter = paths;
	while (iter)
	{
		curr = iter->content;
		if (curr != NULL)
			ft_lstdel(&curr, &ft_del);
		iter->content = NULL;
		iter = iter->next;
	}
}
