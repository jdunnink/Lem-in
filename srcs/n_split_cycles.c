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

static	int	n_cycle(int value, t_list *rem_path)
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

static	int	n_has_cycle(t_list *path_l1)
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

static	int	n_conn(t_data *d, int room_1, int room_2)
{
	int i;
	int links;
	int link;

	i = 0;
	links = d->links_num[room_1];
	while (i < links)
	{
		link = d->links[room_1][i];
		if (link != -1 && link == room_2)
			return (1);
		i++;
	}
	return (0);
}

static	void	n_regen(t_data *d, t_list *branch, t_list *origin)
{
	t_list *iter;
	t_list *branch_tail;

	t_list *tail_ptr;
	t_list *tail;

	tail_ptr = NULL;
	branch_tail = branch;
	while (branch && branch_tail->next)
		branch_tail = branch_tail->next;
	iter = origin;
	while (iter)
	{
		if (n_conn(d, *(int *)iter->content, *(int *)branch_tail->content) == 1 && ft_lstcontains(branch, *(int *)iter->content) == 0)
			tail_ptr = iter;
		iter = iter->next;
	}
	if (tail_ptr != NULL)
	{
		tail = ft_lstcpy(tail_ptr);
		branch_tail->next = ft_lstcpy(tail_ptr);
	}
	return ;
}

static	void	n_split(t_data *d, t_list *split_target, t_list **paths_l2)
{
	int		split;
	t_list *iter;
	t_list *trail;

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
		if (n_new_path(split_target, paths_l2) == 1)
			ft_lstappend(paths_l2, split_target, sizeof(t_list *));
	}
}

static	void	n_parse_lists(t_data *d, t_list **paths_l2, int i)
{
	t_list *iter;
	int j;

	j = 0;
	iter = *paths_l2;
	while (iter)
	{
		if (n_has_cycle(iter->content) == 1)
		{
			n_split(d, iter->content, paths_l2);
		}
		else
			iter = iter->next;
		j++;
	}
}

void	n_split_cycles(t_data *d, t_list **paths_l3)
{
	t_list *iter;
	int		i;

	iter = *paths_l3;
	i = 1;
	while (iter)
	{
		n_parse_lists(d, (t_list **)&iter->content, i);
		iter = iter->next;
		i++;
	}
}