/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_count_cycles.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 14:35:35 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/12 14:35:35 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int	n_count_start(int nb, t_list *path)
{
	t_list	*iter;
	int		count;

	count = 0;
	iter = path;
	while (iter)
	{
		if (*(int *)iter->content == nb)
			count++;
		iter = iter->next;
	}
	return (count);
}

int			n_count_cycles(t_list *path)
{
	int		cycles;
	int		start;
	t_list	*iter;

	cycles = 0;
	iter = path;
	start = *(int *)iter->content;
	cycles = n_count_start(start, iter->next);
	return (cycles);
}
