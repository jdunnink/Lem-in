/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   show_bfs_data.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 16:40:08 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/04 16:40:09 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	show_bfs_data(t_pathdata *data)
{
	int i;

	i = 0;
	while (i < data->rooms)
	{
		ft_putchar('\n');
		ft_putchar(' ');
		ft_putnbr(i);
		ft_putstr(" => ");
		ft_putnbr(data->bfs_data[i][0]);
		ft_putchar(' ');
		ft_putnbr(data->bfs_data[i][1]);
		ft_putchar(' ');
		ft_putnbr(data->bfs_data[i][2]);
		ft_putchar('\n');
		i++;
	}
}
