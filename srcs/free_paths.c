/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_paths.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 02:14:36 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/17 02:14:47 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_paths(t_pathdata *data)
{
	t_list *iter;
	t_list *curr;

	iter = data->paths;
	while (iter)
	{
		curr = iter->content;
		ft_lstdel(&curr, &ft_del);
		iter->content = NULL;
		iter = iter->next;
	}
	ft_lstdel(&data->paths, &ft_del);
	data->paths = NULL;
}
