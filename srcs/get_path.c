/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 02:04:51 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/17 02:04:53 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	get_path takes an index and returns the path currently
**	stored at that location in the paths element.
*/

t_list	*get_path(t_pathdata *path_data, int index)
{
	int		i;
	t_list	*iter;
	t_list	*curr_path;

	iter = path_data->paths;
	i = 0;
	while (iter)
	{
		curr_path = iter->content;
		if (i == index)
			return (curr_path);
		i++;
		iter = iter->next;
	}
	return (NULL);
}
