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
