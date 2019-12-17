/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   del_ant.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 12:01:28 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/12 12:01:28 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	del_ant(void *content, size_t content_size)
{
	t_exp_ant *ant;

	ant = content;
	content_size = 0;
	if (ant == NULL)
		return ;
	if (ant->path != NULL)
		ft_lstdel(&ant->path, &ft_del);
	ant->path = NULL;
	free(ant);
}
