/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   contains.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 16:32:09 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/04 16:32:11 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	contains(t_list *list, int value)
{
	t_list *iter;
	int		val;

	iter = list;
	while (iter)
	{
		val = *(int *)iter->content;
		if (val == value)
			return (1);
		iter = iter->next;
	}
	return (0);
}
