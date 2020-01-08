/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_backup.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 16:25:20 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/01/08 16:25:21 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	create_backup(t_list *paths, t_list **backup)
{
	t_list *target;
	t_list *inner;
	t_list *iter;

	inner = NULL;
	target = NULL;
	iter = paths;
	while (iter)
	{
		inner = ft_lstcpy(iter->content);
		ft_lstappend(&target, inner, sizeof(t_list *));
		inner = NULL;
		iter = iter->next;
	}
	*backup = target;
}
