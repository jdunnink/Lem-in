/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_dump_paths.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 10:23:33 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/06 10:23:34 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	n_dump_paths prints out all the path batches
**	currently contained in paths_l3.
**	paths_l3 is a linked list with pointers to path batches.
**	A path batch is a linked list of paths.
**	A path is a linked list of room indices.
*/

void	n_dump_paths(t_list *paths_l3)
{
	t_list	*iter;
	int		i;

	ft_putchar('\n');
	iter = paths_l3;
	i = 1;
	while (iter)
	{
		show_paths(iter->content);
		ft_putchar('\n');
		iter = iter->next;
		i++;
	}
}
