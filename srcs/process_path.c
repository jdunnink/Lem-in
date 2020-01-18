/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 09:03:08 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/12/10 09:03:08 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>



static	void	add_path(t_list **new_path, t_pathdata *data)
{
	ft_lstappend(&(data->tmp_paths), *new_path, sizeof(t_list *));
	data->total_tmp_paths += 1;
}

static	void	delete_ant(t_list **active_ants)
{
	t_list		*iter;
	t_list		*trail;
	t_exp_ant	*ant;

	iter = *active_ants;
	while (iter)
	{
		ant = iter->content;
		if (ant->path == NULL)
		{
			if (iter == *active_ants)
				ft_lstdelfront(active_ants);
			else if (iter->next == NULL)
				ft_lstdelend(active_ants);
			else
			{
				free(iter->content);
				trail->next = iter->next;
				free(iter);
			}
			return ;
		}
		else
		{
			trail = iter;
			iter = iter->next;
		}
	}
}

#include <stdio.h>

void			process_path(t_pathdata *data)
{
	t_list		*iter;
	t_exp_ant	*ant;

	iter = data->active_ants;
	while (iter)
	{
		ant = iter->content;
		if (ant->room == data->end)
		{
//			printf("	a new path of %lu length has been found!\n", ft_listlen(ant->path));
			add_path(&ant->path, data);
			ant->path = NULL;
			delete_ant(&data->active_ants);
			data->ants_at_start = 0;
			iter = data->active_ants;
		}
		else
			iter = iter->next;
	}
}
