/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_lines.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 14:16:26 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/05 14:16:27 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

void	dump_lines(t_data *data)
{
	t_list	*iter;
	char	*curr;

	iter = data->lines;
	while (iter)
	{
		curr = iter->content;
		ft_putendl(curr);
		iter = iter->next;
	}
	ft_lstdel(&data->lines, &ft_del);
	ft_putchar('\n');
	data->lines = NULL;
}
