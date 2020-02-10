/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_split_cycles.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 09:47:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/06 09:47:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	aggregate of paths contains cycles due to branching
**	cycles are moved into seperate lists and their backend connection to start
**	is regenerated from the room where the path branched.
*/

static	int		n_cycle(int value, t_list *rem_path)
{
	t_list *iter;

	iter = rem_path;
	while (iter)
	{
		if (*(int *)iter->content == value)
			return (1);
		iter = iter->next;
	}
	return (0);
}

static	int		n_has_cycle(t_list *path_l1)
{
	t_list *iter;

	iter = path_l1;
	while (iter->next)
	{
		if (n_cycle(*(int *)(iter->content), iter->next) == 1)
			return (1);
		iter = iter->next;
	}
	return (0);
}

static	void	n_split(t_data *d, t_list *split_target, t_list **paths_l2)
{
	int		split;
	t_list	*iter;
	t_list	*trail;

	split = *(int *)split_target->content;
	iter = split_target->next;
	while (*(int *)iter->content != split && iter)
	{
		trail = iter;
		iter = iter->next;
	}
	if (iter)
	{
		trail->next = NULL;
		n_regen(d, split_target, iter);
		if (n_new_path(iter, paths_l2) == 1)
			ft_lstappend(paths_l2, iter, sizeof(t_list *));
		else
			ft_lstdel(&iter, &ft_del);
	}
}

static	void	n_parse_lists(t_data *d, t_list **paths_l2)
{
	t_list	*iter;

	iter = *paths_l2;
	while (iter)
	{
		if (n_has_cycle(iter->content) == 1)
			n_split(d, iter->content, paths_l2);
		else
			iter = iter->next;
	}
}

void			n_split_cycles(t_data *d, t_list **paths_l3)
{
	t_list	*iter;

	iter = *paths_l3;
	while (iter)
	{
		n_parse_lists(d, (t_list **)&iter->content);
		iter = iter->next;
	}
}
