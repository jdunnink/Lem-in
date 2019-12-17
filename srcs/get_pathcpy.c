/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_pathcpy.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 23:20:41 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/06 21:44:37 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_list	*get_pathcpy(t_pathdata *path_data, int index)
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
		{
			curr_path = ft_lstcpy(curr_path);
			return (curr_path);
		}
		i++;
		iter = iter->next;
	}
	return (NULL);
}
