/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_backup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 16:23:28 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/08 16:23:29 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		free_backup(t_list *backup)
{
	t_list *iter;
	t_list *curr;

	iter = backup;
	while (iter)
	{
		curr = iter->content;
		ft_lstdel(&curr, &ft_del);
		iter->content = NULL;
		iter = iter->next;
	}
	if (backup)
		ft_lstdel(&backup, &ft_del);
	backup = NULL;
}
