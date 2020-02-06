/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   show_paths.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 14:25:31 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/11 14:25:32 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

void	print_path(t_list *path)
{
	t_list *iter;

	iter = path;
	while (iter)
	{
		ft_putnbr(*(int *)(iter->content));
		ft_putchar(' ');
		iter = iter->next;
	}
	ft_putchar('\n');
}

void		show_paths(t_list *paths)
{
	t_list *iter;

	iter = paths;
	while (iter)
	{
		print_path(iter->content);
		iter = iter->next;
	}
}
