/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filter_dups.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 08:16:11 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/08 08:16:12 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int		get_second(t_list *list)
{
	int i;

	i = 0;
	while (list)
	{
		if (i == 1)
			return (*(int *)list->content);
		i++;
		list = list->next;
	}
	return (-1);
}

static	void	del_path(t_list **c_path, t_list **cmp_path, t_list **cmp_trl)
{
	t_list **path_ptr;

	(*cmp_trl)->next = (*cmp_path)->next;
	path_ptr = (t_list **)&((*cmp_path)->content);
	ft_lstdel(path_ptr, &ft_del);
	free(*cmp_path);
	*cmp_path = *c_path;
}

void			filter_dups(t_pathdata *data)
{
	t_list	*curr_path;
	t_list	*cmp_path;
	t_list	*cmp_trail;
	int		curr_val;
	int		cmp_val;

	curr_path = data->paths;
	cmp_path = curr_path->next;
	cmp_trail = curr_path->next;
	while (curr_path->next)
	{
		curr_val = get_second(curr_path->content);
		while (cmp_path)
		{
			cmp_val = get_second(cmp_path->content);
			if (cmp_val == curr_val)
				del_path(&curr_path, &cmp_path, &cmp_trail);
			cmp_trail = cmp_path;
			cmp_path = cmp_path->next;
		}
		curr_path = curr_path->next;
		cmp_path = curr_path->next;
	}
	data->total_paths = ft_listlen(data->paths);
	data->path_threshold = data->total_paths;
}
