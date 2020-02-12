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

/*
**	free_paths takes a pointer to the pathdata struct and
**	frees the paths currently stored in the paths element.
**	the paths element is structured as a linked list of linked lists,
**	with each content ptr pointing to a specific path.
**
**	structure:
**
**	node
**		-->path (linked list)
**		-->next_path (node)
*/

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
